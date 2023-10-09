#include <fstream>
#include <iostream>

struct edge {
  int point1, point2;
  int weight;
  edge(int p1, int p2, int wt) : point1(p1), point2(p2), weight(wt){};
  edge(){};
  bool operator<(const edge& X) const { return weight < X.weight; }
};

void merge_sort(edge* arr, int size) {
  edge* src = arr;
  edge* tmp = new edge[size];
  edge* dst = tmp;
  for (int i = 1; i < size; i *= 2) {
    int start1 = 0;
    int end1 = 0;
    int start2 = 0;
    int end2 = 0;
    int dst_ind = 0;
    for (int j = 0; j < size; j += 2 * i) {
      start1 = j;
      end1 = start1 + i < size ? start1 + i : size;  // if rem < i
      start2 = end1;
      end2 = start2 + i < size ? start2 + i : size;
      while (start1 < end1 && start2 < end2) {
        dst[dst_ind++] =
            src[start1] < src[start2] ? src[start1++] : src[start2++];
      }
      while (start1 < end1) {
        dst[dst_ind++] = src[start1++];
      }
      while (start2 < end2) {
        dst[dst_ind++] = src[start2++];
      }
    }
    std::swap(src, dst);
  }
  if (src != arr) {  // num of iteration: odd or not
    for (int i = 0; i < size; ++i) {
      arr[i] = tmp[i];
    }
  }
  delete[] tmp;
}

int find(int pt, int* pts) { return pt == pts[pt] ? pt : find(pts[pt], pts); }

void union_dsu(int pt1, int pt2, int* pts, int num_of_points) {
  int pt1_set = find(pt1, pts);
  int pt2_set = find(pt2, pts);
  if (pt1_set == pt2_set) {
    return;
  }
  if (pt1_set != pt1 && pt2_set != pt2) {
    for (int i = 0; i < num_of_points; ++i) {
      if (pts[i] == pt1_set) {
        pts[i] = pt2_set;
      }
    }
  } else {
    if (pt1_set != pt1) {
      pts[pt2_set] = pt1_set;
    } else {
      pts[pt1_set] = pt2_set;
    }
  }
}

int main(int argc, char* argv[]) {
  std::ifstream inFile(argv[1]);
  int num_of_edges = 0;
  int num_of_nodes = 0;
  inFile >> num_of_nodes >> num_of_edges;
  edge* edges = new edge[num_of_edges];
  int p1 = 0;
  int p2 = 0;
  int wt = 0;
  for (int i = 0; i < num_of_edges; ++i) {
    inFile >> p1 >> p2 >> wt;
    edges[i] = edge(p1, p2, wt);
  }
  merge_sort(edges, num_of_edges);
  int* pts = new int[num_of_nodes];
  for (int i = 0; i < num_of_nodes; ++i) {
    pts[i] = i;
  }

  int res = 0;
  for (int i = 0; i < num_of_edges; ++i) {
    if (find(edges[i].point1, pts) != find(edges[i].point2, pts)) {
      res += edges[i].weight;
      union_dsu(edges[i].point1, edges[i].point2, pts, num_of_nodes);
    }
  }
  std::cout << res;

  delete[] edges;
  delete[] pts;
  inFile.close();
}
