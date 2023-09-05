import os
import argparse
import matplotlib.pyplot as plt 
import numpy as np
from matplotlib import patches
from matplotlib.animation import FuncAnimation
import pandas as pd
from typing import List

# arg parser
def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--fdir", type=str, default="./results",\
                        help="Directory containing output files in `.csv` format.")
    parser.add_argument("--output", type=str, default="./video.",\
                        help="Filename for saving the animation (use an `.mp4` extension).")
    parser.add_argument("--dpi", type=int, default=300)
    parser.add_argument('--xl', type=float, default=0)
    parser.add_argument('--xu', type=float, default=1)
    parser.add_argument('--yl', type=float, default=0)
    parser.add_argument('--yu', type=float, default=1)
    return parser.parse_args()

# process files
def process_files(fdir: str) -> List[str]:
    fnames = [os.path.join(fdir,f) for f in os.listdir(fdir) if ".csv" in f]
    sorted_filenames = sorted(fnames, key=lambda x: float(x.split('/')[-1].replace('.csv', '')))
    return sorted_filenames

def plot_particles(ax, fname: str):
    data = pd.read_csv(fname, index_col=False).astype(np.float64)  
    ax.clear()
    for index, row in data.iterrows():
        circle = patches.Circle((row['x'], row['y']), radius=row['radius'], edgecolor='tab:gray', facecolor='tab:blue')
        ax.add_artist(circle)
        #ax.annotate(str(index), (row['x'], row['y']), ha='center', va='center')
    ax.set_aspect('equal', 'box')
    ax.set_xlim(args.xl, args.xu)
    ax.set_ylim(args.yl, args.yu)

def animate_particles(files: List[str], filename: str, dpi: int=300):
    # configure plot
    fig, ax = plt.subplots(dpi=dpi)
    
    # define plot function for each frame
    def update(num):
        plot_particles(ax, files[num])

    ani = FuncAnimation(fig, update, frames=len(files), repeat=False)
    ani.save(filename, writer='ffmpeg', fps=60)
    plt.close()

def main():
    global args
    args = parse_args()
    files = process_files(args.fdir)
    animate_particles(files, args.output, args.dpi)
    print(f"Animation completed and saved to {args.output}")

if __name__=="__main__":
    main()