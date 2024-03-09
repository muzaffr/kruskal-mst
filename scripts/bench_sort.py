#!/usr/bin/env python3

from pathlib import Path

from sys import path as syspath
from os import path as ospath
parpath = ospath.abspath(ospath.join(ospath.dirname(__file__), ospath.pardir))
syspath.append(parpath)
from tools.benchmark import Benchmark
from tests.sort.gen import gen as gen_sort
syspath.remove(parpath)


def main():
    sort_bm = Benchmark(
        Path('bin/sort_orig'),
        lambda size: gen_sort(size, 10 ** 9, 818102),
    )
    sort_bm.add_standard(Path('bin/sort_stl_sort'))
    sort_bm.add_standard(Path('bin/sort_stl_heap_sort'))
    speed, memory = sort_bm.benchmark(
        [10 ** i for i in range(1, 8)],
        [10 ** i for i in range(1, 6)],
    )
    with open('data/sort_time.csv', 'w') as f:
        f.write(speed)
    with open('data/sort_mem.csv', 'w') as f:
        f.write(memory)


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('\nScript terminated.')
    except EOFError:
        print('Input terminated.')
