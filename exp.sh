#!/bin/bash -l
#SBATCH --array=0-99
#SBATCH --partition=short
#SBATCH --time=01:00:00
#SBATCH --cpus-per-task=1
#SBATCH --mem=6000
#SBATCH --job-name=OriSp64
#SBATCH --output=/work/mguali01/Ori_spanner/OriSpanner/output
cd /work/mguali01/Ori_spanner/OriSpanner
for s in 8 16 32 64 128 256 512
do 
	srun --output /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/instance${s}_%a.dp.txt /work/mguali01/Ori_spanner/OriSpanner/build_linux/Release/src/OriSpanner -f instances/uniform_$s/uniform_1_${s}_${SLURM_ARRAY_TASK_ID}.txt -a sat1 -d solutions/uniform_$s/
	srun --output /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/instance${s}_%a.sat.txt /work/mguali01/Ori_spanner/OriSpanner/build_linux/Release/src/OriSpanner -f instances/uniform_$s/uniform_1_${s}_${SLURM_ARRAY_TASK_ID}.txt -a sat -d solutions/uniform_$s/
        for l in 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
        do
                srun --output /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/instance${s}_%a.sat_${l}.txt /work/mguali01/Ori_spanner/OriSpanner/build_linux/Release/src/OriSpanner -f instances/uniform_$s/uniform_1_${s}_${SLURM_ARRAY_TASK_ID}.txt -a sat -s -l ${l} -d solutions/uniform_$s/
        done
done
