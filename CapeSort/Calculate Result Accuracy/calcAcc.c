#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[]) {
	if (argc < 2) { 
		printf("Please provide a file to check.\n");
		exit(1);
	}
	
	char *file = argv[1];
	
	FILE *times = fopen(file, "r");
	if (times == NULL) {
		printf("There was an error opening the file.\n");
		exit(2);
	}
	
	int quadCount = 0;
	int timCount  = 0;
	
	int capeCount = 0;
	int capeCorrect = 0;
	
	float quadTime = 0;
	float timTime = 0;
	
	int len = 255;
	char buffer[len+1];
	fgets(buffer, len, times);
	
	char seq[16];
	for (int z = 0; fgets(buffer, len, times) != NULL; z = 0) {
		char sort[16]; // Name of the sort
		for (; buffer[z] != ','; z++) {
			sort[z] = buffer[z];
		}
		sort[z++] = '\0';
		
		if (strcmp(sort, "Cape") == 0) {
			int i;
			
			for (i = 0; buffer[z] != ','; i++, z++) {
				seq[i] = buffer[z];
			}
			seq[i] = '\0';
			z++;
			
			if (strcmp(seq, "Total") ==0) {
				goto Done;
			}
			capeCount++;
			
			while (buffer[z] != ',') {
				z++;
			}
			z++;
			
			char numStr[4];
			for (i = 0; buffer[z] != ','; z++, i++) {
				numStr[i] = buffer[z];
			}
			numStr[i] = '\0';
			z++;
			
			quadCount = atoi(numStr);
			
			for (i = 0; i < sizeof(numStr) / sizeof(char); i++) {
				numStr[i] = '\0';
			}
			
			for (i = 0; buffer[z] != ','; z++, i++) {
				numStr[i] = buffer[z];
			}
			numStr[i] = '\0';
			z++;
			
			timCount = atoi(numStr);
			
			for (i = 0; i < sizeof(numStr) / sizeof(char); i++) {
				numStr[i] = '\0';
			}
		}
		else if (strcmp(sort, "Quad") == 0) {
			while (buffer[z] != ',') {
				z++;
			}
			z++;
			
			char numStr[9];
			int i;
			for (i = 0; buffer[z] != ','; z++, i++) {
				numStr[i] = buffer[z];
			}
			numStr[i] = '\0';
			z++;
			
			quadTime = atof(numStr);
		}
		else if (strcmp(sort, "Tim") == 0) {
			while (buffer[z] != ',') {
				z++;
			}
			z++;
			
			char numStr[9];
			int i;
			for (i = 0; buffer[z] != ','; z++, i++) {
				numStr[i] = buffer[z];
			}
			numStr[i] = '\0';
			z++;
			
			timTime = atof(numStr);
			

			
			float delta = fabs(timTime - quadTime);
/*			printf("Delta: %f\t Tim: %f\t Quad: %f\t D/Q: %f\n", delta, timTime, quadTime, delta/quadTime);*/
			if (delta / quadTime < .1) {
/*				printf("The two were within 10%% on %s\n", seq);*/
			}
			else {
				if (quadTime < timTime && quadCount > timCount) {
					printf("Cape was right choosing Quad for %s\n", seq);
					capeCorrect++;
				}
				else if (quadTime > timTime && quadCount < timCount) {
					printf("Cape was right choosing Tim for %s\n", seq);
					capeCorrect++;
				}
				else if (quadTime < timTime && quadCount < timCount) {
					printf("Cape should have chose Quad for %s\n", seq);
				}
				else if (quadTime > timTime && quadCount > timCount) {
					printf("Cape should have chose Tim for %s\n", seq);
				}
			}
		}
		else {
			printf("Unknown sort encountered; exiting program...\n");
			fclose(times);
			exit(4);
		}
	}
	
	Done:
	printf("Cape was right %d/%d times: %f%%", capeCorrect, capeCount, (float) capeCorrect / (float) capeCount * 100);
	fclose(times);
	return 0;
}
