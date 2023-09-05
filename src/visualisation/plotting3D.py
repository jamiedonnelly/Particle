import os
import argparse
import matplotlib.pyplot as plt 
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
from moviepy.editor import VideoFileClip, concatenate_videoclips
import pandas as pd
from mpi4py import MPI
from typing import List

# arg parser
def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--fdir", type=str, default="./results",\
                        help="Directory containing output files in `.csv` format.")
    parser.add_argument("--odir", type=str, default="./video/.",\
                        help="Filename for saving the animation (use an `.mp4` extension).")
    parser.add_argument("--dpi", type=int, default=300)
    parser.add_argument('--xl', type=float, default=0)
    parser.add_argument('--xu', type=float, default=1)
    parser.add_argument('--yl', type=float, default=0)
    parser.add_argument('--yu', type=float, default=1)
    parser.add_argument('--zl', type=float, default=0)
    parser.add_argument('--zu', type=float, default=1)
    return parser.parse_args()

# MPI init and functions
def init_MPI():
    comm = MPI.COMM_WORLD
    return comm

def process_ranks(comm, args):
    args.world_size, args.rank = comm.size, comm.rank
    args.output = os.path.join(args.odir, f"animation{args.rank}.mp4")

# process files
def process_files(args) -> List[str]:
    fnames = [os.path.join(args.fdir,f) for f in os.listdir(args.fdir) if ".csv" in f]
    sorted_filenames = sorted(fnames, key=lambda x: float(x.split('/')[-1].replace('.csv', '')))
    coef = len(sorted_filenames)/args.world_size
    rank_files = sorted_filenames[int(args.rank*coef):int((args.rank+1)*coef)]
    return rank_files

def plot_particles(ax, fname: str):
    data = pd.read_csv(fname, index_col=False).astype(np.float64)  
    ax.clear()
    for index, row in data.iterrows():
        ax.scatter(row['x'], row['y'], row['z'], s=np.pi * (row['radius']**2) * 4, color='tab:blue')  # Spheres are represented by scatter points with size based on radius.
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.set_xlim(args.xl, args.xu)
    ax.set_ylim(args.yl, args.yu)
    ax.set_zlim(args.zl, args.zu)

def plot_particles(ax, fname: str):
    data = pd.read_csv(fname, index_col=False).astype(np.float64)
    ax.clear()
    for index, row in data.iterrows():
        u = np.linspace(0, 2 * np.pi, 100)
        v = np.linspace(0, np.pi, 100)
        x = row['radius'] * np.outer(np.cos(u), np.sin(v)) + row['x']
        y = row['radius'] * np.outer(np.sin(u), np.sin(v)) + row['y']
        z = row['radius'] * np.outer(np.ones(np.size(u)), np.cos(v)) + row['z']
        
        # Draw the sphere using plot_surface
        ax.plot_surface(x, y, z)
    
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.set_xlim(args.xl, args.xu)
    ax.set_ylim(args.yl, args.yu)
    ax.set_zlim(args.zl, args.zu)

def animate_particles(files: List[str], filename: str, dpi: int=300):
    # configure plot
    fig = plt.figure(dpi=dpi)
    ax = fig.add_subplot(111, projection='3d')
    
    # define plot function for each frame
    def update(num):
        plot_particles(ax, files[num])

    ani = FuncAnimation(fig, update, frames=len(files), repeat=False)
    ani.save(filename, writer='ffmpeg', fps=30)
    plt.close()

def concatenate_videos(args):
    video_files = sorted([os.path.join(args.odir, f) for f in os.listdir(args.odir)])
    print(video_files)
    clips = [VideoFileClip(clip) for clip in video_files]
    final_clip = concatenate_videoclips(clips, method="compose")
    final_clip.write_videofile("./animation.mp4", codec="libx264")

def main():
    global particle_paths
    particle_paths = {}
    global args
    args = parse_args()
    comm = init_MPI()
    process_ranks(comm, args)
    files = process_files(args)
    animate_particles(files, args.output, args.dpi)
    if args.rank==0:
        concatenate_videos(args)
    print(f"Animation completed and saved...")

if __name__=="__main__":
    main()
