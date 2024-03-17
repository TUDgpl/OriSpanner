#!/bin/bash -l
#SBATCH --array=0-99
#SBATCH --partition=short
#SBATCH --time=01:00:00
#SBATCH --cpus-per-task=1
#SBATCH --mem=6000
#SBATCH --job-name=OriSp64
#SBATCH --output=/work/mguali01/Ori_spanner/OriSpanner/output
cd /work/mguali01/Ori_spanner/OriSpanner
for s in 32
do 
	for g in range(0, 1, 49999)
	do 
		srun --output /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/instance${s}_${g}.dp.txt /work/mguali01/Ori_spanner/OriSpanner/build_linux/Release/src/OriSpanner -f instances_32/uniform_$s/uniform_1_${s}_${g}.txt -a sat1 -d solutions/uniform_$s/
		srun --output /work/mguali01/Ori_spanner/OriSpanner/solutions/uniform_$s/instance${s}_${g}.sat.txt /work/mguali01/Ori_spanner/OriSpanner/build_linux/Release/src/OriSpanner -f instances_32/uniform_$s/uniform_1_${s}_${g}.txt -a sat -d solutions/uniform_$s/
	done 
done
