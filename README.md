# Candidate-Elimination

This repo contains the implementation of the Candidate Elimination algorithm in C++. Given the Hypothesis space <b>H</b> and a set of examples <b>E</b>, the algorithm builds the version space. The examples are fed into the algorithm sequentially and each example reduces the Version space by removing the hypotheses that are inconsistent with that example. This is achieved by updating the general and specific boundary for each new example.


The algorithm as given in <b>Machine Learning</b> book by <i>Tom Mitchell</i> is given below


	Initialize G to the  set of maximally general hypotheses in H 
	Initialize S to the set of maximally specific hypotheses in H 
	For each training example d, do 

		If d is a positive  example 
			Remove from G any hypothesis inconsistent with d 
			For each hypothesis s in S that is not consistent with d 
				Remove s from S 
				Add to S all minimal generalizations h of s such that 
					h is consistent with d, and some member of G is more general than h  
				Remove from S any hypothesis that is more general than another hypothesis in S 

		If d is a negative example 
			Remove from S any hypothesis inconsistent with d 
			For each hypothesis g in G that is not consistent with d 
				Remove g from G 
				Add  to G all minimal specializations h of g such that 
					h is consistent with d, and some member of S is more  specific than h 
				Remove from G any hypothesis that is less general  than another hypothesis in G


