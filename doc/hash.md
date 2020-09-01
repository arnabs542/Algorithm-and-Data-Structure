<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [How to design Key](#how-to-design-key)
    - [sorted](#sorted)
    - [Offset](#offset)
    - [subTree serialization results](#subtree-serialization-results)
    - [Matrix index](#matrix-index)
    - [Geometry: coordination](#geometry-coordination)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# How to design Key

### sorted

When the order of each element in the string/array doesn't matter, you can use the sorted string/array as the key.

### Offset

If you only care about the offset of each value, usually the offset from the first value, you can use the offset as the key.

### subTree serialization results

In a tree, you might want to directly use the TreeNode as key sometimes. But in most cases, the serialization of the subtree might be a better idea.

### Matrix index

In a matrix, you might want to use the row index or the column index as key.

### Geometry: coordination

In a Sudoku, you can combine the row index and the column index to identify which block this element belongs to.
Sometimes, in a matrix, you might want to aggregate the values in the same diagonal line. 