#!/bin/bash -l
#SBATCH --array=92-93
#SBATCH --partition=short
#SBATCH --time=01:00:00
#SBATCH --cpus-per-task=1
#SBATCH --mem=6000
#SBATCH --job-name=OriSp64
#SBATCH --output=/work/mguali01/Ori_spanner/OriSpanner/output
cd /work/mguali01/Ori_spanner/OriSpanner
for s in 64
do 
	srun --output /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/instance${s}_%a.dp.txt /work/mguali01/Ori_spanner/OriSpanner/build_linux/Release/src/OriSpanner -f instances/uniform_$s/uniform_1_${s}_${SLURM_ARRAY_TASK_ID}.txt -a dp -d solutions/uniform_$s/
	srun --output /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/instance${s}_%a.sat.txt /work/mguali01/Ori_spanner/OriSpanner/build_linux/Release/src/OriSpanner -f instances/uniform_$s/uniform_1_${s}_${SLURM_ARRAY_TASK_ID}.txt -a sat -d solutions/uniform_$s/
done
