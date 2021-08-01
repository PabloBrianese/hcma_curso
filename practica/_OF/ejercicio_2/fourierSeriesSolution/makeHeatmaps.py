import pandas as pd

df = pd.read_csv("dat/fourierSeriesSolution.csv")

timesteps = []
for t_val in df.t.drop_duplicates():
    timesteps.append(
        df.loc[df.t == t_val].drop(columns=["t"]).pivot("y", "x", "concentration")
    )


from matplotlib import pyplot as plt
from matplotlib import ticker
import seaborn as sns

for timestep in range(len(timesteps)):
    fig, ax = plt.subplots()
    sns.heatmap(
        timesteps[timestep],
        vmin=0.0, vmax=1.0,
        xticklabels=10,
        yticklabels=10,
        ax=ax
    )
    ax.yaxis.set_major_formatter(ticker.StrMethodFormatter("{x:.0f}"))
    ax.xaxis.set_major_formatter(ticker.StrMethodFormatter("{x:.0f}"))
    ax.set_title("Solución usando series de Fourier")
    ax.set_xlabel("indice x del nodo")
    ax.set_ylabel("indice y del nodo")
    plt.subplots_adjust(bottom=0.15)
    fig.savefig(f"dat/timestep{timestep:03}.png")
