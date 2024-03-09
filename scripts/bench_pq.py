#!/usr/bin/env python3

from pathlib import Path

from sys import path as syspath
from os import path as ospath
parpath = ospath.abspath(ospath.join(ospath.dirname(__file__), ospath.pardir))
syspath.append(parpath)
from tools.benchmark import Benchmark
from tests.pq.gen import gen as gen_pq
syspath.remove(parpath)


def main():
    sort_bm = Benchmark(
        Path('bin/pq_orig'),
        lambda size: gen_pq(size, size // 2, 10 ** 9, 818102),
    )
    sort_bm.add_standard(Path('bin/pq_stl_pq'))
    sort_bm.add_standard(Path('bin/pq_stl_set'))
    speed, memory = sort_bm.benchmark(
        [10 ** i for i in range(1, 7)],
        [10 ** i for i in range(1, 5)],
    )
    print(speed)
    print(memory)
    with open('data/pq_time.csv', 'w') as f:
        f.write(speed)
    with open('data/pq_mem.csv', 'w') as f:
        f.write(memory)


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('\nScript terminated.')
    except EOFError:
        print('Input terminated.')
