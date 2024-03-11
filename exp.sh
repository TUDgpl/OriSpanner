#!/bin/bash -l
#SBATCH --array=0-99
#SBATCH --partition=short
#SBATCH --time=01:00:00
#SBATCH --cpus-per-task=1
#SBATCH --mem=6000
#SBATCH --job-name=Spanner64
cd /work/mguali01/Ori_spanner/OriSpanner
for s in 8 16 32 64
do 
	srun --output /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/instance$s_%a.dp.txt ./OriSpanner -f instances/uniform_$s/uniform_1_$s_$SLURM_ARRAY_TASK_ID.txt -a dp -d /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/
	srun --output /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/instance$s_%a.sat.txt ./OriSpanner -f instances/uniform_$s/uniform_1_$s_$SLURM_ARRAY_TASK_ID.txt -a sat -d /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/
	srun --output /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/instance$s_%a.sat_2.txt ./OriSpanner -f instances/uniform_$s/uniform_1_$s_$SLURM_ARRAY_TASK_ID.txt -a sat -s -l 2 -d /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/
	srun --output /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/instance$s_%a.sat_3.txt ./OriSpanner -f instances/uniform_$s/uniform_1_$s_$SLURM_ARRAY_TASK_ID.txt -a sat -s -l 3 -d /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/
	srun --output /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/instance$s_%a.sat_4.txt ./OriSpanner -f instances/uniform_$s/uniform_1_$s_$SLURM_ARRAY_TASK_ID.txt -a sat -s -l 4 -d /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/
	srun --output /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/instance$s_%a.sat_5.txt ./OriSpanner -f instances/uniform_$s/uniform_1_$s_$SLURM_ARRAY_TASK_ID.txt -a sat -s -l 5 -d /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/
done
