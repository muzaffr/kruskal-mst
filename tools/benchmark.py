from csv import writer as csvwriter
from io import StringIO
from pathlib import Path
from re import findall
from subprocess import run, DEVNULL, PIPE
from time import perf_counter_ns as perftime
from typing import List, Tuple, Callable


class Benchmark:

    def __init__(self, target: Path, gen: Callable[[int], str]) -> None:
        self._gen = gen
        self._targets = [target]
        self._iterations: int = 5

    @property
    def iterations(self) -> int:
        return self._iterations
    
    @iterations.setter
    def iterations(self, value: int) -> None:
        self._iterations = value

    def add_standard(self, bm: Path) -> None:
        '''Add a standard/comparison for benchmarking.'''
        self._targets.append(bm)

    def _bench_speed(self, inp: bytes) -> List[float]:
        '''Run benchmarks for speed.'''
        times = []
        for target in self._targets:
            t1 = perftime()
            p = run(target, input=inp, stdout=DEVNULL, stderr=PIPE)
            dt = perftime() - t1
            if p.returncode != 0:
                dt = float('inf')
            times.append(dt / 1e6)
        return times

    def _bench_memory(self, inp: bytes) -> List[int]:
        '''Run benchmarks for memory.'''
        memorys = []
        for target in self._targets:
            p = run(['valgrind', target], input=inp, stdout=DEVNULL, stderr=PIPE)
            memory = findall(
                r'total heap usage: [\d,]+ allocs, [\d,]+ frees, ([\d,]+) bytes allocated',
                p.stderr.decode(),
            )[0]
            memorys.append(int(memory.replace(',', '')))
        return memorys

    def benchmark(self, speed_range: List[int], memory_range: List[int]) -> Tuple[str, str]:
        '''Run speed and memory benchmarking.'''
        header = ['size'] + list(map(lambda x: x.stem, self._targets))
        speed_str = StringIO()
        speed_csv = csvwriter(speed_str)
        speed_csv.writerow(header)
        for size in speed_range:
            aggr_times = [[] for _ in self._targets]
            inp = self._gen(size).encode('utf8')
            for _ in range(self.iterations):
                times = self._bench_speed(inp)
                for i, t in enumerate(times):
                    aggr_times[i].append(t)
            median_times = list(map(lambda x: sorted(x)[len(x) // 2], aggr_times))
            speed_csv.writerow([size] + median_times)
        speed_data = speed_str.getvalue()
        speed_str.close()

        memory_str = StringIO()
        memory_csv = csvwriter(memory_str)
        memory_csv.writerow(header)
        for size in memory_range:
            inp = self._gen(size).encode('utf8')
            memorys = self._bench_memory(inp)
            # print(memorys)
            memory_csv.writerow([size] + memorys)
            # print(size, median_times, memorys)
        memory_data = memory_str.getvalue()
        memory_str.close()

        return (speed_data, memory_data)
