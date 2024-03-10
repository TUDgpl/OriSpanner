#!/bin/bash -l
#SBATCH --array=0-99
#SBATCH --partition=short
#SBATCH --time=01:00:00
#SBATCH --cpus-per-task=1
#SBATCH --mem=6000
#SBATCH --job-name=Spanner64
#SBATCH --output=/work/mcarrehs/instance_64/instance64_%a.out.txt
cd /work/mguali01/Ori_spanner/OriSpanner
./OriSpanner -f instances/uniform_8/uniform_1_8_$SLURM_ARRAY_TASK_ID.txt
