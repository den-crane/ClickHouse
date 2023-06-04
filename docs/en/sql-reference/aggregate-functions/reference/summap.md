---
slug: /en/sql-reference/aggregate-functions/reference/summap
sidebar_position: 141
---

# sumMap

Syntax: [sumMap(key <Array>, value <Array>)](../../data-types/array.md) or [sumMap(Tuple(key <Array>, value <Array>))](../../data-types/tuple.md) or [sumMap(<Map>(key, value))](../../data-types/map.md)

Totals the `value` array according to the keys specified in the `key` array/map.

Passing tuple of keys and values arrays is a synonym to passing two arrays of keys and values.

The number of elements in `key` and `value` must be the same for each row that is totaled.

Returns a tuple of two arrays or map in case of Map datatype: keys in sorted order, and values summed for the corresponding keys.

Example:

``` sql
CREATE TABLE sum_map(
    date Date,
    timeslot DateTime,
    statusMap Nested(
        status UInt16,
        requests UInt64
    ),
    statusMapTuple Tuple(Array(Int32), Array(Int32)),
    statusMapMap Map(Int32, Int32)
) ENGINE = Log;
    
INSERT INTO sum_map VALUES
    ('2000-01-01', '2000-01-01 00:00:00', [1, 2, 3], [10, 10, 10], ([1, 2, 3], [10, 10, 10]), ([1, 2, 3], [10, 10, 10])),
    ('2000-01-01', '2000-01-01 00:00:00', [3, 4, 5], [10, 10, 10], ([3, 4, 5], [10, 10, 10]), ([3, 4, 5], [10, 10, 10])),
    ('2000-01-01', '2000-01-01 00:01:00', [4, 5, 6], [10, 10, 10], ([4, 5, 6], [10, 10, 10]), ([4, 5, 6], [10, 10, 10])),
    ('2000-01-01', '2000-01-01 00:01:00', [6, 7, 8], [10, 10, 10], ([6, 7, 8], [10, 10, 10]), ([6, 7, 8], [10, 10, 10]));

SELECT
    timeslot,
    sumMap(statusMap.status, statusMap.requests),
    sumMap(statusMapTuple),
    sumMap(statusMapMap)
FROM sum_map
GROUP BY timeslot
```

``` text
┌────────────timeslot─┬─sumMap(statusMap.status, statusMap.requests)─┬─sumMap(statusMapTuple)─────────┬─sumMap(statusMapMap)───────┐
│ 2000-01-01 00:00:00 │ ([1,2,3,4,5],[20,20,30,10,10])               │ ([1,2,3,4,5],[20,20,30,10,10]) │ {1:20,2:20,3:30,4:10,5:10} │
│ 2000-01-01 00:01:00 │ ([4,5,6,7,8],[10,10,20,10,10])               │ ([4,5,6,7,8],[10,10,20,10,10]) │ {4:10,5:10,6:20,7:10,8:10} │
└─────────────────────┴──────────────────────────────────────────────┴────────────────────────────────┴────────────────────────────┘
```
