from csv import reader as csvreader
import matplotlib.pyplot as plt
from pathlib import Path

class LogLogBarChart:

    def __init__(self, sheet) -> None:
        self._sheet = sheet

    def set_xlabel(self, label: str) -> None:
        self._xlabel = label

    def set_title(self, title: str) -> None:
        self._title = title

    def plot(self, path: Path) -> None:

        with open(self._sheet) as csvf:
            reader = csvreader(csvf)
            header = next(reader)[1:]
            data = [[] for _ in header]
            labels = []
            for row in reader:
                labels.append(int(row[0]))
                for i, v in enumerate(row[1:]):
                    data[i].append(int(v))
            self._data = data

        k = len(data[1:])

        bar_width = 0.2
        bar_positions = range(len(data[0]))

        fig, ax = plt.subplots()

        for i, values in enumerate(data):
            bars = ax.barh([x + (i - (k - 1) / 2) * bar_width for x in bar_positions], values, bar_width, label=header[i], log=True)

            for bar, value in zip(bars, values):
                ax.text(bar.get_width(), bar.get_y() + bar.get_height() / 2, f'{value}', ha='left', va='center', fontsize='small')

        ax.grid(True, which='both', linestyle='--', linewidth=0.5)
        ax.legend()
        ax.set_yticks(bar_positions)
        ax.set_yticklabels(labels)
        ax.set_xlabel(self._xlabel)
        ax.set_ylabel('Input size (n)')
        ax.set_title(self._title)

        plt.savefig(path, bbox_inches='tight', dpi=200)
