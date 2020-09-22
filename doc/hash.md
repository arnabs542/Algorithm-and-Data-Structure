<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [How to design Key](#how-to-design-key)
  - [sorted](#sorted)
  - [Offset](#offset)
  - [subTree serialization results](#subtree-serialization-results)
  - [Matrix index](#matrix-index)
    - [Geometry problem](#geometry-problem)
      - [Perfect Rectangle](#perfect-rectangle)
  - [Geometry: coordination](#geometry-coordination)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# How to design Key

## sorted

When the order of each element in the string/array doesn't matter, you can use the sorted string/array as the key.

## Offset

If you only care about the offset of each value, usually the offset from the first value, you can use the offset as the key.

## subTree serialization results

In a tree, you might want to directly use the TreeNode as key sometimes. But in most cases, the serialization of the subtree might be a better idea.

## Matrix index

In a matrix, you might want to use the row index or the column index as key.

### Geometry problem

#### Perfect Rectangle

https://leetcode.com/problems/perfect-rectangle/

Given N axis-aligned rectangles where N > 0, determine if they all together form an exact cover of a rectangular region.

Each rectangle is represented as a bottom-left point and a top-right point. For example, a unit square is represented as [1,1,2,2]. (coordinate of bottom-left point is (1, 1) and top-right point is (2, 2)).

```CPP

//the large rectangle area should be equal to the sum of small rectangles
//count of all the points should be even, and that of all the four corner points should be one

class Solution {
private:
    inline string getKey(int x, int y) { return to_string(x) + "-" + to_string(y); }
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        if (rectangles.empty() || rectangles[0].empty()) return false;
        int x1 = INT_MAX, y1 = INT_MAX, x2 = INT_MIN, y2 = INT_MIN, area = 0;
        unordered_set<string> s;
        for (auto v : rectangles) {
            x1 = min(x1, v[0]);
            y1 = min(y1, v[1]);
            x2 = max(x2, v[2]);
            y2 = max(y2, v[3]);
            area += (v[2] - v[0]) * (v[3] - v[1]);
            string a = getKey(v[0], v[1]), b = getKey(v[0], v[3]), c = getKey(v[2], v[1]), d = getKey(v[2], v[3]);
            if (!s.erase(a)) s.insert(a);
            if (!s.erase(b)) s.insert(b);
            if (!s.erase(c)) s.insert(c);
            if (!s.erase(d)) s.insert(d);
        }
        return s.count(getKey(x1, y1))
            && s.count(getKey(x1, y2))
            && s.count(getKey(x2, y1))
            && s.count(getKey(x2, y2))
            && s.size() == 4
            && area == (x2 - x1) * (y2 - y1);
    }
};
```




## Geometry: coordination

In a Sudoku, you can combine the row index and the column index to identify which block this element belongs to.
Sometimes, in a matrix, you might want to aggregate the values in the same diagonal line. 