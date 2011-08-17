#ifndef _OPTIONS_H
#define _OPTIONS_H

typedef enum heuristic_metric heuristic_metric;
enum heuristic_metric {
	HAMMING,
	MANHATTAN
};

extern int VERBOSE;
extern heuristic_metric HEURISTIC;

#endif