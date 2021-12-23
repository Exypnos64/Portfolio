#define _XOPEN_SOURCE
#include <sys/time.h>
#include <time.h>

#define SORT_NAME sorter
#define SORT_TYPE int
/* You can redefine the comparison operator.
   The default is
#define SORT_CMP(x, y)  ((x) < (y) ? -1 : ((x) == (y) ? 0 : 1))
   but the one below is often faster for integer types.
*/
#define SORT_CMP(x, y)  (x - y)
#define MAX(x, y)(((x) > (y) ? (x) : (y)))
#define MIN(x, y)(((x) < (y) ? (x) : (y)))
#define SORT_CSWAP(x, y) { SORT_TYPE _sort_swap_temp = MAX((x), (y)); (x) = MIN((x), (y)); (y) = _sort_swap_temp; }
#include "sort.h"

/*
------------------------------------------------
*/
/*
	Copyright (C) 2014-2020 Igor van den Hoven ivdhoven@gmail.com
*/

/*
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
	quadsort 1.1
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct stat st = {0};


typedef int CMPFUNC(const void * a,
    const void * b);
/*
------------------------------------------------
*/
void verify(int * dst, const int size) {
    int i;

    for (i = 1; i < size; i++) {
        if (dst[i - 1] > dst[i]) {
            printf("Verify failed! at %d\n", i);
            /*
                  for (i = i - 2; i < SIZE; i++) {
                    printf(" %lld", (long long) dst[i]);
                  }
            */
            printf("\n");
            break;
        }
    }
}

void swap(int * a, int * b) {
    int temp;
    temp = * a;
    * a = * b;
    * b = temp;
}
/*
------------------------------------------------
*/
// benchmarking utilities

long long utime() {
    struct timeval now_time;

    gettimeofday(&now_time, NULL);

    return now_time.tv_sec * 1000000LL + now_time.tv_usec;
}
/*
------------------------------------------------
*/
//tim sort
float test_tim(int * z_array, int * r_array, int max) {
    double start, end, total = 0;
    
    memcpy(z_array, r_array, max * sizeof(int));
    start = utime();
    sorter_tim_sort(z_array, max);
    end = utime();
    total += end - start;
    verify(z_array, max);

    return total / 1000000.0;
}
//selection sort
float test_selection(int * z_array, int * r_array, int max) {
	double start, end, total = 0;

	memcpy(z_array, r_array, max * sizeof(int));
	start = utime();
	sorter_selection_sort(z_array, max);
	end = utime();
	total += end - start;
	verify(z_array, max);
    
	return total / 1000000.0;
}
//bubble sort
float test_bubble(int * z_array, int * r_array, int max) {
	double start, end, total = 0;

	memcpy(z_array, r_array, max * sizeof(int));
	start = utime();
	sorter_bubble_sort(z_array, max);
	end = utime();
	total += end - start;
	verify(z_array, max);
    
	return total / 1000000.0;
}
//bitonic sort
float test_bitonic(int * z_array, int * r_array, int max) {
	double start, end, total = 0;

	memcpy(z_array, r_array, max * sizeof(int));
	start = utime();
	sorter_bitonic_sort(z_array, max);
	end = utime();
	total += end - start;
	verify(z_array, max);
    
	return total / 1000000.0;
}
//merge sort
float test_merge(int * z_array, int * r_array, int max) {
	double start, end, total = 0;

	memcpy(z_array, r_array, max * sizeof(int));
	start = utime();
	sorter_merge_sort(z_array, max);
	end = utime();
	total += end - start;
	verify(z_array, max);
    
	return total / 1000000.0;
}
//binary insertion
float test_binary_insertion(int * z_array, int * r_array, int max) {
	double start, end, total = 0;

	memcpy(z_array, r_array, max * sizeof(int));
	start = utime();
	sorter_binary_insertion_sort(z_array, max);
	end = utime();
	total += end - start;
	verify(z_array, max);
    
	return total / 1000000.0;
}
//heap sort
float test_heap(int * z_array, int * r_array, int max) {
	double start, end, total = 0;

	memcpy(z_array, r_array, max * sizeof(int));
	start = utime();
	sorter_heap_sort(z_array, max);
	end = utime();
	total += end - start;
	verify(z_array, max);
    
	return total / 1000000.0;
}
//shell sort
float test_shell(int * z_array, int * r_array, int max) {
	double start, end, total = 0;

	memcpy(z_array, r_array, max * sizeof(int));
	start = utime();
	sorter_shell_sort(z_array, max);
	end = utime();
	total += end - start;
	verify(z_array, max);
    
	return total / 1000000.0;
}
//in-place merge sort
float test_in_place_merge(int * z_array, int * r_array, int max) {
	double start, end, total = 0;

	memcpy(z_array, r_array, max * sizeof(int));
	start = utime();
	sorter_merge_sort_in_place(z_array, max);
	end = utime();
	total += end - start;
	verify(z_array, max);
    
	return total / 1000000.0;
}
//grail sort
float test_grail(int * z_array, int * r_array, int max) {
	double start, end, total = 0;

	memcpy(z_array, r_array, max * sizeof(int));
	start = utime();
	sorter_grail_sort(z_array, max);
	end = utime();
	total += end - start;
	verify(z_array, max);
    
	return total / 1000000.0;
}
//sqrt sort
float test_sqrt(int * z_array, int * r_array, int max) {
	double start, end, total = 0;

	memcpy(z_array, r_array, max * sizeof(int));
	start = utime();
	sorter_sqrt_sort(z_array, max);
	end = utime();
	total += end - start;
	verify(z_array, max);
    
	return total / 1000000.0;
}
//rec stable sort
float test_rec_stable(int * z_array, int * r_array, int max) {
	double start, end, total = 0;

	memcpy(z_array, r_array, max * sizeof(int));
	start = utime();
	sorter_rec_stable_sort(z_array, max);
	end = utime();
	total += end - start;
	verify(z_array, max);
    
	return total / 1000000.0;
}
//grail sort dyn buffer
float test_grail_dyn_buffer(int * z_array, int * r_array, int max) {
	double start, end, total = 0;

	memcpy(z_array, r_array, max * sizeof(int));
	start = utime();
	sorter_grail_sort_dyn_buffer(z_array, max);
	end = utime();
	total += end - start;
	verify(z_array, max);
    
	return total / 1000000.0;
}
//Shaker
//grail sort dyn buffer
float test_Shaker(int * z_array, int * r_array, int max) {
	double start, end, total = 0;

	memcpy(z_array, r_array, max * sizeof(int));
	start = utime();
		//---------shaker sort-------------
        int i, j, k, m = max;
        for (i = 0; i < m;) {
            for (j = i + 1; j < m; j++) {
                if (z_array[j] < z_array[j - 1])
                    swap( & z_array[j], & z_array[j - 1]);
            }
            m--;
            for (k = m - 1; k > i; k--) {
                if (z_array[k] < z_array[k - 1])
                    swap( & z_array[k], & z_array[k - 1]);
            }
            i++;
        }
        //----------------------------------
	end = utime();
	total += end - start;
	verify(z_array, max);
    
	return total / 1000000.0;
}
/*
------------------------------------------------
*/
void quarter_sort32(void * array, int key, size_t nmemb, CMPFUNC * cmp) {
    int * pta = array;

    switch (nmemb) {
    case 1:
        pta[1] = pta[0];
        pta[0] = key;
        return;
    case 2:
        pta[2] = pta[1];

        if (cmp( & key, & pta[0]) < 0) {
            pta[1] = pta[0];
            pta[0] = key;
        } else {
            pta[1] = key;
        }
        return;
    default:
        pta[3] = pta[2];

        if (cmp( & key, & pta[1]) < 0) {
            pta[2] = pta[1];

            if (cmp( & key, & pta[0]) < 0) {
                pta[1] = pta[0];
                pta[0] = key;
            } else {
                pta[1] = key;
            }
        } else {
            pta[2] = key;
        }
        return;
    }
}

void quarter_sort64(void * array, long long key, size_t nmemb, CMPFUNC * cmp) {
    long long * pta = array;

    switch (nmemb) {
    case 1:
        pta[1] = pta[0];
        pta[0] = key;
        return;
    case 2:
        pta[2] = pta[1];

        if (cmp( & key, & pta[0]) < 0) {
            pta[1] = pta[0];
            pta[0] = key;
        } else {
            pta[1] = key;
        }
        return;
    default:
        pta[3] = pta[2];

        if (cmp( & key, & pta[1]) < 0) {
            pta[2] = pta[1];

            if (cmp( & key, & pta[0]) < 0) {
                pta[1] = pta[0];
                pta[0] = key;
            } else {
                pta[1] = key;
            }
        } else {
            pta[2] = key;
        }
        return;
    }
}

void swap_sort32(void * array, size_t nmemb, CMPFUNC * cmp) {
    size_t offset;
    register int swap, * pta;

    pta = array;

    for (offset = 0; offset + 4 <= nmemb; offset += 4) {
        if (cmp( & pta[0], & pta[1]) > 0) {
            swap = pta[0];
            pta[0] = pta[1];
            pta[1] = swap;
        }

        if (cmp( & pta[1], & pta[2]) > 0) {
            if (cmp( & pta[0], & pta[2]) > 0) {
                swap = pta[2];
                pta[2] = pta[1];
                pta[1] = pta[0];
                pta[0] = swap;
            } else {
                swap = pta[2];
                pta[2] = pta[1];
                pta[1] = swap;
            }
        }

        if (cmp( & pta[2], & pta[3]) > 0) {
            if (cmp( & pta[0], & pta[3]) > 0) {
                swap = pta[3];
                pta[3] = pta[2];
                pta[2] = pta[1];
                pta[1] = pta[0];
                pta[0] = swap;
            } else if (cmp( & pta[1], & pta[3]) > 0) {
                swap = pta[3];
                pta[3] = pta[2];
                pta[2] = pta[1];
                pta[1] = swap;
            } else {
                swap = pta[3];
                pta[3] = pta[2];
                pta[2] = swap;
            }
        }

        pta += 4;
    }

    for (swap = 1; offset + swap < nmemb; swap++) {
        if (cmp( & pta[swap], & pta[swap - 1]) < 0) {
            quarter_sort32(pta, pta[swap], swap, cmp);
        }
    }
}

void swap_sort64(void * array, size_t nmemb, CMPFUNC * cmp) {
    size_t offset;
    register long long swap, * pta;

    pta = array;

    for (offset = 0; offset + 4 <= nmemb; offset += 4) {
        if (cmp( & pta[0], & pta[1]) > 0) {
            swap = pta[0];
            pta[0] = pta[1];
            pta[1] = swap;
        }

        if (cmp( & pta[1], & pta[2]) > 0) {
            if (cmp( & pta[0], & pta[2]) > 0) {
                swap = pta[2];
                pta[2] = pta[1];
                pta[1] = pta[0];
                pta[0] = swap;
            } else {
                swap = pta[2];
                pta[2] = pta[1];
                pta[1] = swap;
            }
        }

        if (cmp( & pta[2], & pta[3]) > 0) {
            if (cmp( & pta[0], & pta[3]) > 0) {
                swap = pta[3];
                pta[3] = pta[2];
                pta[2] = pta[1];
                pta[1] = pta[0];
                pta[0] = swap;
            } else if (cmp( & pta[1], & pta[3]) > 0) {
                swap = pta[3];
                pta[3] = pta[2];
                pta[2] = pta[1];
                pta[1] = swap;
            } else {
                swap = pta[3];
                pta[3] = pta[2];
                pta[2] = swap;
            }
        }

        pta += 4;
    }

    for (swap = 1; offset + swap < nmemb; swap++) {
        if (cmp( & pta[swap], & pta[swap - 1]) < 0) {
            quarter_sort64(pta, pta[swap], swap, cmp);
        }
    }
}

void quad_sort32(void * array, void * swap, size_t block, size_t nmemb, CMPFUNC * cmp) {
    size_t offset;
    register int * pta, * pts, * c, * c_max, * d, * d_max, * end;

    end = (int * ) array + nmemb;

    while (block < nmemb) {
        offset = 0;

        while (offset + block < nmemb) {
            pta = (int * ) array + offset;

            d_max = pta + block;

            if (cmp(d_max - 1, d_max) <= 0) {
                if (offset + block * 3 < nmemb) {
                    d_max = pta + block * 2;

                    if (cmp(d_max - 1, d_max) <= 0) {
                        d_max = offset + block * 4 <= nmemb ? pta + block * 3 : end;

                        if (cmp(d_max - 1, d_max) <= 0) {
                            offset += block * 4;
                            continue;
                        }
                    }
                } else if (offset + block * 2 < nmemb) {
                    d_max = offset + block * 2 <= nmemb ? pta + block * 2 : end;

                    if (cmp(d_max - 1, d_max) <= 0) {
                        offset += block * 4;
                        continue;
                    }
                } else {
                    offset += block * 4;
                    continue;
                }
            }

            pts = (int * ) swap;

            c = pta;
            c_max = pta + block;

            d = c_max;
            d_max = offset + block * 2 <= nmemb ? d + block : end;

            if (cmp(c_max - 1, d_max - 1) <= 0) {
                while (c < c_max) {
                    while (cmp(c, d) > 0) {
                        * pts++ = * d++;
                    }
                    * pts++ = * c++;
                }
                while (d < d_max)
                    *
                    pts++ = * d++;
            } else if (cmp(c, d_max - 1) > 0) {
                while (d < d_max)
                    *
                    pts++ = * d++;

                while (c < c_max)
                    *
                    pts++ = * c++;
            } else {
                while (d < d_max) {
                    while (cmp(c, d) <= 0) {
                        * pts++ = * c++;
                    }
                    * pts++ = * d++;
                }

                while (c < c_max) {
                    * pts++ = * c++;
                }
            }

            if (offset + block * 2 < nmemb) {
                c = pta + block * 2;

                if (offset + block * 3 < nmemb) {
                    c_max = c + block;
                    d = c_max;
                    d_max = offset + block * 4 <= nmemb ? d + block : end;

                    if (cmp(c_max - 1, d_max - 1) <= 0) {
                        while (c < c_max) {
                            while (cmp(c, d) > 0) {
                                * pts++ = * d++;
                            }
                            * pts++ = * c++;
                        }
                        while (d < d_max)
                            *
                            pts++ = * d++;
                    } else if (cmp(c, d_max - 1) > 0) {
                        while (d < d_max)
                            *
                            pts++ = * d++;
                        while (c < c_max)
                            *
                            pts++ = * c++;
                    } else {
                        while (d < d_max) {
                            while (cmp(c, d) <= 0) {
                                * pts++ = * c++;
                            }
                            * pts++ = * d++;
                        }
                        while (c < c_max)
                            *
                            pts++ = * c++;
                    }
                } else {
                    while (c < end)
                        *
                        pts++ = * c++;
                }
            }

            pts = (int * ) swap;

            c = pts;

            if (offset + block * 2 < nmemb) {
                c_max = c + block * 2;

                d = c_max;
                d_max = offset + block * 4 <= nmemb ? d + block * 2 : pts + nmemb - offset;

                if (cmp(c_max - 1, d_max - 1) <= 0) {
                    while (c < c_max) {
                        while (cmp(c, d) > 0) {
                            * pta++ = * d++;
                        }
                        * pta++ = * c++;
                    }
                    while (d < d_max)
                        *
                        pta++ = * d++;
                } else if (cmp(c, d_max - 1) > 0) {
                    while (d < d_max)
                        *
                        pta++ = * d++;
                    while (c < c_max)
                        *
                        pta++ = * c++;
                } else {
                    while (d < d_max) {
                        while (cmp(d, c) > 0) {
                            * pta++ = * c++;
                        }
                        * pta++ = * d++;
                    }
                    while (c < c_max)
                        *
                        pta++ = * c++;
                }
            } else {
                d_max = pts + nmemb - offset;

                while (c < d_max)
                    *
                    pta++ = * c++;
            }
            offset += block * 4;
        }
        block *= 4;
    }
}

void quad_sort64(void * array, void * swap, size_t block, size_t nmemb, CMPFUNC * cmp) {
    size_t offset;
    register long long * pta, * pts, * c, * c_max, * d, * d_max, * end;

    end = (long long * ) array + nmemb;

    while (block < nmemb) {
        offset = 0;

        while (offset + block < nmemb) {
            pta = (long long * ) array + offset;

            d_max = pta + block;

            if (cmp(d_max - 1, d_max) <= 0) {
                if (offset + block * 3 < nmemb) {
                    d_max = pta + block * 2;

                    if (cmp(d_max - 1, d_max) <= 0) {
                        d_max = offset + block * 4 <= nmemb ? pta + block * 3 : end;

                        if (cmp(d_max - 1, d_max) <= 0) {
                            offset += block * 4;
                            continue;
                        }
                    }
                } else if (offset + block * 2 < nmemb) {
                    d_max = offset + block * 2 <= nmemb ? pta + block * 2 : end;

                    if (cmp(d_max - 1, d_max) <= 0) {
                        offset += block * 4;
                        continue;
                    }
                } else {
                    offset += block * 4;
                    continue;
                }
            }

            pts = (long long * ) swap;

            c = pta;
            c_max = pta + block;

            d = c_max;
            d_max = offset + block * 2 <= nmemb ? d + block : end;

            if (cmp(c, d_max - 1) > 0) {
                while (d < d_max)
                    *
                    pts++ = * d++;

                while (c < c_max)
                    *
                    pts++ = * c++;
            } else {
                if (cmp(c_max - 1, d_max - 1) <= 0) {
                    while (c < c_max) {
                        while (cmp(c, d) > 0) {
                            * pts++ = * d++;
                        }
                        * pts++ = * c++;
                    }
                    while (d < d_max)
                        *
                        pts++ = * d++;
                } else {
                    while (d < d_max) {
                        while (cmp(c, d) <= 0) {
                            * pts++ = * c++;
                        }
                        * pts++ = * d++;
                    }

                    while (c < c_max) {
                        * pts++ = * c++;
                    }
                }
            }

            if (offset + block * 2 < nmemb) {
                c = pta + block * 2;

                if (offset + block * 3 < nmemb) {
                    c_max = c + block;
                    d = c_max;
                    d_max = offset + block * 4 <= nmemb ? d + block : end;

                    if (cmp(c, d_max - 1) > 0) {
                        while (d < d_max)
                            *
                            pts++ = * d++;
                        while (c < c_max)
                            *
                            pts++ = * c++;
                    } else {
                        if (cmp(c_max - 1, d_max - 1) <= 0) {
                            while (c < c_max) {
                                while (cmp(c, d) > 0) {
                                    * pts++ = * d++;
                                }
                                * pts++ = * c++;
                            }
                            while (d < d_max)
                                *
                                pts++ = * d++;
                        } else {
                            while (d < d_max) {
                                while (cmp(c, d) <= 0) {
                                    * pts++ = * c++;
                                }
                                * pts++ = * d++;
                            }
                            while (c < c_max)
                                *
                                pts++ = * c++;
                        }
                    }
                } else {
                    while (c < end)
                        *
                        pts++ = * c++;
                }
            }

            pts = (long long * ) swap;

            c = pts;

            if (offset + block * 2 < nmemb) {
                c_max = c + block * 2;

                d = c_max;
                d_max = offset + block * 4 <= nmemb ? d + block * 2 : pts + nmemb - offset;

                if (cmp(c, d_max - 1) > 0) {
                    while (d < d_max)
                        *
                        pta++ = * d++;
                    while (c < c_max)
                        *
                        pta++ = * c++;
                } else {
                    if (cmp(c_max - 1, d_max - 1) <= 0) {
                        while (c < c_max) {
                            while (cmp(c, d) > 0) {
                                * pta++ = * d++;
                            }
                            * pta++ = * c++;
                        }
                        while (d < d_max)
                            *
                            pta++ = * d++;
                    } else {
                        while (d < d_max) {
                            while (cmp(d, c) > 0) {
                                * pta++ = * c++;
                            }
                            * pta++ = * d++;
                        }
                        while (c < c_max)
                            *
                            pta++ = * c++;
                    }
                }

            } else {
                d_max = pts + nmemb - offset;

                while (c < d_max)
                    *
                    pta++ = * c++;
            }
            offset += block * 4;
        }
        block *= 4;
    }
}

void quadsort(void * array, size_t nmemb, size_t size, CMPFUNC * cmp) {
    void * swap;

    swap = malloc(nmemb * size);

    if (size == sizeof(int)) {
        swap_sort32(array, nmemb, cmp);

        quad_sort32(array, swap, 4, nmemb, cmp);
    } else if (size == sizeof(long long)) {
        swap_sort64(array, nmemb, cmp);

        quad_sort64(array, swap, 4, nmemb, cmp);
    }

    free(swap);
}

int cmp_int(const void * a,
    const void * b) {
    return *(int * ) a - * (int * ) b;
}

int cmp_str(const void * a,
    const void * b) {
    return strcmp( * (const char ** ) a, *(const char ** ) b);
}

float test_quad(int * z_array, int * r_array, int max) {
    double start, end, total = 0;

    memcpy(z_array, r_array, max * sizeof(int));
    start = utime();
    quadsort(z_array, max, sizeof(int), cmp_int);
    end = utime();
    total += end - start;
    verify(z_array, max);
    
    return total / 1000000.0;
}

float test_quick(int * z_array, int * r_array, int max) {
	double start, end, total = 0;

	memcpy(z_array, r_array, max * sizeof(int));
	start = utime();
	qsort(z_array, max, sizeof(int), cmp_int);
	end = utime();
	total += end - start;
	verify(z_array, max);
    
	return total / 1000000.0;
}

// 1=true, 0=false + added
int inBuffer(char* sort_buffer, char* sort) {
	char temp_sort[16];
	if(strstr(sort_buffer, sort) != NULL) {
		return 1;
	}
	else {
		strcat(sort_buffer, ",");
		strcat(sort_buffer, sort);
		return 0;
	}
}

// 1=true, 0=false
int sameOptions(int* sizes, int* sequence, int* prevSize, int* prevSeq) {
	for (int i = 0; i < 5; i++) {
		if (sizes[i] != prevSize[i]) {
			return 0;
		}
		if (sequence[i] != prevSeq[i]) {
			return 0;
		}
	}
	return 1;
}

#define SORT_TYPE int
#define SORT_CMP(x, y)  (x - y)
void cape_sort_dict(SORT_TYPE* dst, int size, FILE* dictionary, char* capeSeq, char* outSamples, char* outSort, int repeated) {
/*void cape_sort_dict(SORT_TYPE* dst, int size, FILE* smallDict, FILE* largeDict, char* outSamples, char* outSort, int repeated) { */
	/*---------* Start Cape Sort *---------*/
/*	FILE* dictionary;*/
	printf("Cape Log:\n");
	double sampleStart = utime();
	/*---------* Sample the Data *---------*/
	
/*	if (size < 32 * 1024) { // When the data is less than 32K*/
/*		printf("Data too small for dictionary\nDefaulting to Quad...\n");*/
/*		strcpy(outSort, "Small-DefQuad");*/
/*		quadsort(dst, size, sizeof(int), cmp_int);*/
/*	*/
/*		double runStop = utime();*/
/*		printf("Sorting time: %f\n", (runStop - sampleStart) / 1000000.0);*/
/*		return;*/
/*	}*/
/*	else if (32 * 1024 <= size && size < 128 * 1024) { // When the data is between 32K and 128K*/
/*		printf("Used Small Dictionary\n");*/
/*		dictionary = smallDict;*/
/*	}*/
/*	else { // When the data is 128K or above*/
/*		printf("Used Large Dictionary\n");*/
/*		dictionary = largeDict;*/
/*	}*/
	
	int samples = size * 0.1; // Number of samples we need to take
	int window = 5; // The size of each window
	int groups = 4; // The number of windows we look at: samples / window (hardcoded)
	int increment = size / (groups + 1); // How far apart each window is (beginning to beginning)
	int cursor = 0 - (int)(window/2) + increment; // The int that will reference each point in a window, starts on first window
	
	char sampleSeq[groups]; // Asc: A, Des: D, Con: C, Ran: R
	int samCur = 0; // The cursor for moving through the sampleSeq array
	printf("Size: %d\nSamples: %d\nWindow: %d\nGroups: %d\nincrement: %d\n", size, samples, window, groups, increment);
	printf("Samples:\n");
	for (int winNum = 0; winNum < groups; cursor += increment - window, winNum++) {
		int comp[window-1]; // The amount of comparisons is 1 less than the amount in a window
		int asc = 0, des = 0, con = 0; // The amount of each comparison
		
/*		printf("Cursor before: %d\n", cursor);*/
		
		printf("[%d", dst[cursor]);
		char cursorNum[16];
		if (repeated == 0) {
			strcat(outSamples, "[");
			snprintf(cursorNum, sizeof cursorNum, "%d", dst[cursor]);
			strcat(outSamples, cursorNum);
		}
		for (int i = 0; i < window - 1; i++, cursor++) { // Compare items in the window
			if (SORT_CMP(dst[cursor], dst[cursor+1]) < 0) { // Asc: 1
				asc++;
			}
			else if (SORT_CMP(dst[cursor], dst[cursor+1]) > 0) { // Des: 2
				des++;
			}
			else if (SORT_CMP(dst[cursor], dst[cursor+1]) == 0) { // Con: 3
				con++;
			}
			
			printf(" %d", dst[cursor+1]);
			if (repeated == 0) {
				for (int i = 0; i < sizeof(cursorNum) / sizeof(char); i++) {
					cursorNum[i] = '\0';
				}
				strcat(outSamples, " ");
				snprintf(cursorNum, sizeof cursorNum, "%d", dst[cursor+1]);
				strcat(outSamples, cursorNum);
			}
		}
		printf("] ");
		if(repeated == 0) {
			strcat(outSamples, "],");
		}
		cursor++;
		
		if (asc == window-1) {
			sampleSeq[samCur++] = 'A';
			printf("Ascending\n");
		}
		else if (des == window-1) {
			sampleSeq[samCur++] = 'D';
			printf("Descending\n");
		}
		else if (con == window-1) {
			sampleSeq[samCur++] = 'C';
			printf("Constant\n");
		}
		else {
			sampleSeq[samCur++] = 'R';
			printf("Random\n");
		}
/*		printf("Cursor after: %d\n", cursor);*/
	}
	if (repeated == 0) {
		int i;
		for (i = 0; i < samCur; i++) {
			capeSeq[i] = sampleSeq[i];
		}
		capeSeq[i] = '\0';
		printf("Wrote sequence & samples\n");
	}
	
	/**---------* Sample the Data *---------**/
	double sampleStop = utime();
	printf("Sample time:  %f\n", (sampleStop - sampleStart) / 1000000.0);
	double chooseStart = utime();
	/*---------* Search Dictionary  *---------*/
	
	rewind(dictionary);
	
	// Setting up buffer to read dictionary line by line
	int len = 255;
	char buffer[len+1];
	buffer[len] = '\0';
	
	// Skipping the first line (headers)
	fgets(buffer, len, dictionary);
	
	char sort[16]; // Name of sort
	while (fgets(buffer, len, dictionary) != NULL) {
		int z; // Cursor on line
		char dictSeq[groups]; // Sequence of data types
		for (int i = 0; i < sizeof(dictSeq) / sizeof(char); i++) {
			dictSeq[i] = 0;
		}
		
		// Get the name of the sort
		for (z = 0; buffer[z] != ','; z++) {
			sort[z] = buffer[z];
		}
		sort[z++] = '\0';
		if (repeated == 0) {
			strcpy(outSort, sort);
		}
		int y = 0;
		
		// Get the sequence
		int t;
		for (t = 0; buffer[z] != ','; t++) {
			dictSeq[t] = buffer[z++];
		}
		
/*		printf("\nDict Seq:");*/
/*		for (int i = 0; i < groups; i++) {*/
/*			printf(" %c", dictSeq[i]);*/
/*		}*/
/*		printf(", Sample Seq:");*/
/*		for (int i = 0; i < groups; i++) {*/
/*			printf(" %c", sampleSeq[i]);*/
/*		}*/
/*		printf("\n");*/
		
		// Check sequence
		for (int i = 0; i < groups; i++) {
			if (dictSeq[i] != sampleSeq[i]) { // Not a match
/*				printf("%d: Sequence not match\n\n", i);*/
				goto noMatch; // Next reference
			}
		}
		
		printf("Match Found\n");
		goto matchFound; // Match found, moving on
		
		noMatch: // Not a match
		for (int i = 0; i < sizeof(sort) / sizeof(char); i++) {
			sort[i] = '\0';
		}
		continue;
	}
	strcpy(sort, "Quad"); // No match found, default to Quad Sort

	matchFound:
	;
	/**---------* Search Dictionary *---------**/
	double chooseStop = utime();
	printf("Choose time:  %f\n\nSort reads: %s\n", (chooseStop - chooseStart) / 1000000.0, sort);
	double runStart = utime();
	/*---------* Run Recommended Sort *---------*/
	
	if (strcmp(sort, "Quad") == 0) {
		printf("Chose Quad\n");
		quadsort(dst, size, sizeof(int), cmp_int);
	}
		
	else if (strcmp(sort, "Tim") == 0) {
		printf("Chose Tim\n");
		sorter_tim_sort(dst, size);
	}

	else if (strcmp(sort, "Quick") == 0) {
		printf("Chose Quick\n");
		qsort(dst, size, sizeof(int), cmp_int);
	}
		
	else if (strcmp(sort, "Selection") == 0) {
		printf("Chose Selection\n");
		sorter_selection_sort(dst, size);
	}
		
	else if (strcmp(sort, "Bubble") == 0) {
		printf("Chose Bubble\n");
		sorter_bubble_sort(dst, size);
	}
		
	else if (strcmp(sort, "Bitonic") == 0) {
		printf("Chose Bitonic\n");
		sorter_bitonic_sort(dst, size);
	}
		
	else if (strcmp(sort, "Merge") == 0) {
		printf("Chose Merge\n");
		sorter_merge_sort(dst, size);
	}
		
	else if (strcmp(sort, "BinaryInsertion") == 0) {
		printf("Chose BinaryInsertion\n");
		sorter_binary_insertion_sort(dst, size);
	}
		
	else if (strcmp(sort, "Heap") == 0) {
		printf("Chose Heap\n");
		sorter_heap_sort(dst, size);
	}
		
	else if (strcmp(sort, "Shell") == 0) {
		printf("Chose Shell\n");
		sorter_shell_sort(dst, size);
	}
		
	else if (strcmp(sort, "MergeInPlace") == 0) {
		printf("Chose MergeInPlace\n");
		sorter_merge_sort_in_place(dst, size);
	}
		
	else if (strcmp(sort, "Grail") == 0) {
		printf("Chose Grail\n");
		sorter_grail_sort(dst, size);
	}
		
	else if (strcmp(sort, "Sqrt") == 0) {
		printf("Chose Sqrt\n");
		sorter_sqrt_sort(dst, size);
	}
		
	else if (strcmp(sort, "RecStable") == 0) {
		printf("Chose RecStable\n");
		sorter_rec_stable_sort(dst, size);
	}
		
	else if (strcmp(sort, "GrailDyn") == 0) {
		printf("Chose GrailDyn\n");
		sorter_grail_sort_dyn_buffer(dst, size);
	}
		
	else if (strcmp(sort, "Shaker") == 0) {
		printf("Chose GrailDyn\n");
    	int i, j, k, m = size;
	    for (i = 0; i < m;) {
	        for (j = i + 1; j < m; j++) {
	            if (dst[j] < dst[j - 1])
	                swap( & dst[j], & dst[j - 1]);
	        }
	        m--;
	        for (k = m - 1; k > i; k--) {
	            if (dst[k] < dst[k - 1])
	                swap( & dst[k], & dst[k - 1]);
	        }
	        i++;
	    }
	}
	
	else {
/*		printf("Defaulted to Quad\n");*/
		strcpy(outSort, "DefQuad");
		quadsort(dst, size, sizeof(int), cmp_int);
	}
	
	/**---------* Run Recommended Sort *---------**/
	double runStop = utime();
	printf("Sorting time: %f\n", (runStop - runStart) / 1000000.0);
	/**---------* Stop Cape Sort *---------**/
}

#define SORT_TYPE int
#define SORT_CMP(x, y)  (x - y)
void cape_sort_test(SORT_TYPE* dst, int size, int* quadCount, int* timCount, int* tieCount) {
	
	srand(utime());
	int samplePoint = rand() % 1000;
	int percentSize = 200;
	
	/*---------* Output Samples in File *---------*/
	
	// Making output file for samples
	if (stat("Samples", &st) == -1) { // If the Times directory does not exist, create it
		mkdir("Samples", 0777);
	}
	
	char fileName[31] = "Samples/";
	char chNumber[5];
	snprintf(chNumber, sizeof chNumber, "%d", samplePoint);
	strcat(fileName, chNumber);
	strcat(fileName, ".txt");
	printf("%s\n", &fileName[8]);
	
	FILE *samples = fopen(fileName, "w");
	if (samples == NULL) {
		printf("There was an error outputing the files.");
		exit(1024);
	}
	
	/**---------* Output Samples in File *---------**/
	/*---------* Start Cape Sort *---------*/
	printf("Cape Log:\n");
	double sampleStart = utime();
	/*---------* Sample the Data *---------*/
	SORT_TYPE *sample, *quadSam, *timSam;
	sample = malloc(size / percentSize * sizeof(int)); // The array that will hold the samples
	quadSam = malloc(size / percentSize * sizeof(int)); // The samples Quad will Sort
	timSam = malloc(size / percentSize * sizeof(int)); // The samples Tim will Sort
	
	int sampleSize = 0;
	for (int i = samplePoint; i < size; i+=percentSize) {
		sample[sampleSize++] = dst[i];
		
	}
	
	/**---------* Sample the Data *---------**/
	double sampleStop = utime();
	printf("Start point: %d\n", samplePoint);
	printf("Sample Size: %d\n", sampleSize);
	printf("Sample time:  %f\n", (sampleStop - sampleStart) / 1000000.0);
	/*---------* Print Samples to File *---------*/
	
	fprintf(samples, "[%d", sample[0]);
	for (int i = 1; i < sampleSize; i++) {
		fprintf(samples, ", %d", sample[i]);
	}
	fprintf(samples, "]\n");
	fclose(samples);
	
	/**---------* Print Samples to File *---------**/
	double testStart = utime();
	/*---------* Test Sorts  *---------*/
	
	float quad, tim;
	
	// Quad
	memcpy(quadSam, sample, sampleSize);
	printf("Cape testing Quad: ");
	double quadStart = utime();
	quadsort(quadSam, sampleSize, sizeof(int), cmp_int);
	double quadStop = utime();
	quad = (quadStop - quadStart) / 1000000.0;
	printf("%f\n", quad);
	
	// Tim
	memcpy(timSam, sample, sampleSize);
	printf("Cape testing Tim:  ");
	double timStart = utime();
	sorter_tim_sort(timSam, sampleSize);
	double timStop = utime();
	tim = (timStop - timStart) / 1000000.0;
	printf("%f\n", tim);
	
	printf("Tim / Quad: %f\n", tim / quad);
	
	// Determine fastest sorting algorithm
	float best = INT_MAX;
	char sort[16];
	
	if (quad == tim) {
		printf("Quad and Tim are equal\n");
		++*tieCount;
	}
	if (quad < best) {
		best = quad;
		strcpy(sort, "Quad");
	}
	if (tim < best) {
		best = tim;
		strcpy(sort, "Tim");
	}
	
	/**---------* Test Sorts *---------**/
	double testStop = utime();
	printf("Test time:  %f\n\nSort reads: %s\n", (testStop - testStart) / 1000000.0, sort);
	double runStart = utime();
	/*---------* Run Recommended Sort *---------*/
	
	if (strcmp(sort, "Quad") == 0) {
		printf("Chose Quad\n");
		++*quadCount;
		quadsort(dst, size, sizeof(int), cmp_int);
	}
		
	else if (strcmp(sort, "Tim") == 0) {
		printf("Chose Tim\n");
		++*timCount;
		sorter_tim_sort(dst, size);
	}
	
	else {
		printf("Defaulted to Quad\n");
/*		(&defQuadCount)++;*/
		quadsort(dst, size, sizeof(int), cmp_int);
	}
	
	/**---------* Run Recommended Sort *---------**/
	double runStop = utime();
	printf("Sorting time: %f\n", (runStop - runStart) / 1000000.0);
	/**---------* Stop Cape Sort *---------**/
}

float test_cape(int * z_array, int * r_array, int size, int* quadCount, int* timCount, int* tieCount) {
/*float test_cape(int * z_array, int * r_array, int size, FILE* dictionary, char* capeSeq, char* outSamples, char* outSort, int repeated) {*/
/*float test_cape(int * z_array, int * r_array, int size, FILE* smallDict, FILE* largeDict, char* outSamples, char* outSort, int repeated) {*/
	double start, end, total = 0;

	memcpy(z_array, r_array, size * sizeof(int));
	start = utime();
	cape_sort_test(z_array, size, quadCount, timCount, tieCount);
/*	cape_sort_dict(z_array, size, dictionary, capeSeq, outSamples, outSort, repeated);*/
/*	cape_sort_dict(z_array, size, smallDict, largeDict, outSamples, outSort, repeated);*/
	end = utime();
	total += end - start;
	verify(z_array, size);
    
	return total / 1000000.0;
}

void generate(int *arr, int datanumber, char unit, int parts, char *seq) {
	srand(utime());
	// Varaible Defaults
	int max = 1;
	int random;
	int n = 0;
	
	// Used to help with multiple type generation
	char choice = seq[0];
	char previous = choice;
	// For the length of the sequence
	for (int i = 0; i < parts; i++) {
		choice = seq[i];
		// Determining size for this part of the data
		if (choice != 0) {
			int datasize = 0;
			if (unit == 'k' || unit == 'K') {
				datasize = datanumber * 1024;
			}
			if (unit == 'm' || unit == 'M') {
				datasize = datanumber * 1024 * 1024;
			}
			if (unit == 'g' || unit == 'G') {
				datasize = datanumber * 1024 * 1024 * 1024;
			}
			if (datasize != 0) {
				max = datasize / parts;
			} else {
				max = datanumber / parts;
			}
		}
		// Create data based on the part of the sequence
		int num = (rand() % (64 * 1024)) - (32 * 1024);
		switch (choice) {
		    case 'A':
		        //----------------------ascending
		        printf("Generated Ascending\n");
		        for (int i = 0; i < max; i++, n++) {
		        	random = (rand() % (2 - 1 + 1)) + 1;
		            num += random;
		            arr[n] = num;
		        }
		        break;
		    
		    case 'D':
		        //--------------------------------descending
		        printf("Generated Descending\n");
		        for (int i = 0; i < max; i++, n++) {
		            random = (rand() % (2 - 1 + 1)) + 1;
		            num -= random;
		            arr[n] = num;
		        }
		        break;
		    
		    case 'C':
		        //--------------------------------constant
		        printf("Generated Constant\n");
		        for (int i = 0; i < max; i++, n++) {
		            arr[n] = num;
		        }
		        break;
			
			case 'R':
		        //--------------------------------random
		        printf("Generated Random\n");
		        for (int i = 0; i < max; i++, n++) {
		            random = (rand() % (2 - 1 + 1)) + 1;
		            if (i % 2) {
		                num += random;
		            } else {
		                num -= random;
		            }
		            arr[n] = num;
		        }
		        break;

		    case 0:
		    	printf("\n");
		    	return;
		        break;
		        
		    default:
		    	return;
		}
		// Increment to the next number in the sequence
		previous = choice;
    }
}

int increment(char *seq, int inc) {
	if (seq[inc] == 'A') {
		seq[inc] = 'C';
	}
	else if (seq[inc] == 'C') {
		seq[inc] = 'D';	
	}
	else if (seq[inc] == 'D') {
		seq[inc] = 'R';
	}
	else if (seq[inc] == 'R') {
		seq[inc] = 'A';
		increment(seq, inc-1);
	}
}

int generate_seqs(int parts, int amount, char seqs[amount+1][parts]) {
	char seq[parts];
	char ter[parts];
	int i;
	for (i = 0; i < parts; i++) { // Initializes array to all 'A's
		seq[i] = 'A';
	}
	seq[i] = '\0';
	
	for (i = 0; i < parts; i++) { // Initializes termination array to all 'R's
		ter[i] = 'R';
	}
	ter[i] = '\0';
/*	printf("%s %s\n", seq, ter);*/
	
	for (i = 0; i < parts; i++) { // Sets first sequence
		seqs[0][i] = seq[i];
	}
	
	for (i=1; strcmp(seq, ter) != 0; i++) { // Sets the other sequences
		increment(seq, parts-1);
		for (int j = 0; j < parts; j++) {
			seqs[i][j] = seq[j];
		}
	}
}

void writeAvg(char* sort, char* seq, float time, FILE* output) { // Automates the file writing process
	// Buffer
	int length = 512;
	char buffer[length+1];
	for (int i = 0; i <= length; i++) {
		buffer[i] = '\0';
	}
	
	// Sort
	strcat(buffer, sort);
	strcat(buffer, ",");
	// Sequence
	strcat(buffer, seq);
	strcat(buffer, ",");
	// Time
	char average[16];
	snprintf(average, sizeof average, "%f", time);
	strcat(buffer, average);
	strcat(buffer, ",\n");
	
	// Write the buffer to the document
	fputs(buffer, output);
}

void writeAvgCape_Dict(char* sort, char* chosenSort, char* seq, float time ,char* capeSeq, char* samples, FILE* output) { // The same as writeAvg but includes the sort Cape Sort used and it's samples
	// Buffer
	int length = 512;
	char buffer[length+1];
	for (int i = 0; i <= length; i++) {
		buffer[i] = '\0';
	}
	
	// Sorts
	strcat(buffer, sort);
	strcat(buffer, " - ");
	strcat(buffer, chosenSort);
	strcat(buffer, ",");
	
	// Sequence
	strcat(buffer, seq);
	strcat(buffer, ",");
	// Time
	char average[16];
	snprintf(average, sizeof average, "%f", time);
	strcat(buffer, average);
	strcat(buffer, ",");
	// Cape Sequence
	strcat(buffer, capeSeq);
	strcat(buffer, ",");
	
	// Samples
	strcat(buffer, samples);
	strcat(buffer, "\n");
	
	// Write the buffer to the document
	fputs(buffer, output);
}

void writeAvgCape_Test(char* sort, char* seq, float time, int quadCount, int timCount, int tieCount, FILE* output) { // The same as writeAvg but includes the amount of times sorts were chosen and tied
	// Buffer
	int length = 512;
	char buffer[length+1];
	for (int i = 0; i <= length; i++) {
		buffer[i] = '\0';
	}
	
	// Sorts
	strcat(buffer, sort);
	strcat(buffer, ",");
	// Sequence
	strcat(buffer, seq);
	strcat(buffer, ",");
	// Time
	char average[16];
	snprintf(average, sizeof average, "%f", time);
	strcat(buffer, average);
	strcat(buffer, ",");
	
	// Quad Count
	char quad[5];
	snprintf(quad, sizeof quad, "%d", quadCount);
	strcat(buffer, quad);
	strcat(buffer, ",");
	// Tim Count
	char tim[5];
	snprintf(tim, sizeof tim, "%d", timCount);
	strcat(buffer, tim);
	strcat(buffer, ",");
	// Tie Count
	char tie[5];
	snprintf(tie, sizeof tie, "%d", tieCount);
	strcat(buffer, tie);
	strcat(buffer, ",\n");	
	
	// Write the buffer to the document
	fputs(buffer, output);
}

void printTime(float time, FILE* output) {
	int hours = time/3600;
	int minutes = time/60 - hours*60;
	float seconds = time - minutes*60 - hours*3600;
	if (hours > 0) {
		if (hours > 1) {
			fprintf(output, " %d hours", hours);
		}
		else {
			fprintf(output, " %d hour", hours);
		}
	}
	if (minutes > 0) {
		if (minutes > 1) {
			fprintf(output, " %d minutes", minutes);
		}
		else {
			fprintf(output, " %d minute", minutes);
		}
	}
	fprintf(output, " %f seconds", seconds);
}

int main(int argc, char *argv[]) {
/*	int datanumbers[8] = {128, 256, 512, 1, 2, 4, 8, 16};*/
/*	char units[8] = {'k', 'k', 'k', 'm', 'm', 'm', 'm', 'm'};*/
	int* datanumbers = malloc(16 * sizeof(int));
	char* units = malloc(16 * sizeof(char));
	
	int dataDef[] = {100};
	char unitDef[] = "m";
	int multiTotal;

	if (argc > 1) {
	multiTotal = 0;
		for (int i = 0; i < argc - 1; i++) {
			datanumbers[i] = (int) strtol(argv[i+1], (char**) NULL, 10);

			int n = 0, j = datanumbers[i];
			while (j != 0) {
				j /= 10;
				n++;
			}
			units[i] = (char) argv[i+1][n];
			
			multiTotal++;
		}
	}
	else {
		multiTotal = sizeof(dataDef) / sizeof(int);
		memcpy(datanumbers, dataDef, sizeof(dataDef));
		memcpy(units, unitDef, sizeof(unitDef));
	}
	
	printf("Size(s) chosen: %d%c", datanumbers[0], units[0]);
	for (int i = 1; i < multiTotal; i++) {
		printf(", %d%c", datanumbers[i], units[i]);
	}
	printf("\n");
	
	printf("About to run %d size(s)...\n\n", multiTotal);
	
	// To run multiple data sizes automatically
	for (int multiTest = 0; multiTest < multiTotal; multiTest++) {
	int datanumber = datanumbers[multiTest];
	char unit = units[multiTest];
	/*---------* Get Data Size *---------*/
	/*---------* Data User Changes *---------*/
	
	int repeat_times = 100;
	int parts = 4;
	
	if (multiTest == 0) {
		parts = 6;
	}
	else if (multiTest == 1) {
		parts = 8;
	}
	
	/**---------* Data User Changes *---------**/
	double start = utime();
	
	// Determining size of data and setting up arrays
	int datasize = 0;
	if (unit == 'k' || unit == 'K') {
        datasize = datanumber * 1024;
    }
    if (unit == 'm' || unit == 'M') {
        datasize = datanumber * 1024 * 1024;
    }
    if (unit == 'g' || unit == 'G') {
    	datasize = datanumber * 1024 * 1024 * 1024;
    }
	static int max;
	if (datasize != 0) {
	    max = datasize;
	} else {
	    max = datanumber;
	}
	
	int amount = 1;
	for (int i = 0; i < parts; i++) {
		amount *= 4; // 4 is for A, C, D, and R
	}
	
	/**---------* Get Data Size *---------**/
	/*---------* Read Testing Methods *---------*/
	
/*	double dictStart = utime();*/
/*	FILE *dictionary;*/
/*	*/
/*	if (parts == 4) {*/
/*		dictionary = fopen("Dictionaries/CapeSort_Dictionary-4.csv", "r");*/
/*		if (dictionary == NULL) {*/
/*			printf("There was an error opening the dictionary.\n");*/
/*			exit(1);*/
/*		}*/
/*	}*/
/*	else if (parts == 6) {*/
/*		dictionary = fopen("Dictionaries/CapeSort_Dictionary-6.csv", "r");*/
/*		if (dictionary == NULL) {*/
/*			printf("There was an error opening the dictionary.\n");*/
/*			exit(1);*/
/*		}*/
/*	}*/
/*	else if (parts == 8) {*/
/*		dictionary = fopen("Dictionaries/CapeSort_Dictionary-8.csv", "r");*/
/*		if (dictionary == NULL) {*/
/*			printf("There was an error opening the dictionary.\n");*/
/*			exit(1);*/
/*		}*/
/*	}*/
/*	else {*/
/*		printf("There is not a dictionary to support %d-sequence.\n", parts);*/
/*		exit(-1);*/
/*	}*/

/*	FILE *smallDict = fopen("Dictionaries/CapeSort_Dictionary-S.csv", "r");*/
/*	if (smallDict == NULL) {*/
/*		printf("There was an error opening the small dictionary.");*/
/*		exit(1);*/
/*	}*/
/*	*/
/*	FILE *largeDict = fopen("Dictionaries/CapeSort_Dictionary-L.csv", "r");*/
/*	if (largeDict == NULL) {*/
/*		printf("There was an error opening the small dictionary.");*/
/*		exit(2);*/
/*	}*/
	
/*	double dictStop = utime();*/
/*	printf("Open Dictionary time:  %f\t\n", (dictStop - dictStart) / 1000000.0);*/
	
	FILE *sortFile = fopen("Sorts.csv", "r");
	if (sortFile == NULL) {
		printf("There was an error opening the csv.");
		exit(4);
	}
	// Making output file for averages
	if (stat("Times", &st) == -1) { // If the Times directory does not exist, create it
		mkdir("Times", 0777);
	}
	
	char fileName[31] = "Times/Sequence_Times_";
	char chNumber[5];
	snprintf(chNumber, sizeof chNumber, "%d", datanumber);
	char chUnit[2];
	snprintf(chUnit, sizeof chUnit, "%c", unit);
	strcat(fileName, chNumber);
	strcat(fileName, chUnit);
	strcat(fileName, ".csv");
	printf("%s\n", &fileName[6]);
	
	FILE *seqTimes = fopen(fileName, "w");
	if (seqTimes == NULL) {
		printf("There was an error outputing the files.");
		exit(8);
	}
	fputs("Sorts,Sequence,Time,Quad Count,Tim Count,Tied,\n", seqTimes);
/*	fputs("Sorts,Sequence,Time,Cape Sequence,Sample Sequence 1,Sample Sequence 2,Sample Sequence 3,Sample Sequence 4,\n", seqTimes);*/
	printf("Opened times file\n");
	// End output file for averages creation
	
	// Output file for the fastest sort of each sequence
	char fastFile[31] = "Times/Fastest_";
	strcat(fastFile, chNumber);
	strcat(fastFile, chUnit);
	strcat(fastFile, ".csv");
	printf("%s\n", &fastFile[6]);
	
	FILE *fastest = fopen(fastFile, "w");
	if (fastest == NULL) {
		printf("There was an error outputing the files.");
		exit(16);
	}
	fputs("Sorts,Sequence,Time,\n", fastest);
	// End output file for fastest sorts
	
	int length = 512;
	char sorts[length+1];
	int i;
	for (i = 0; i < length+1; i++) {
		sorts[i] = '\0';
	}
	
	/**---------* Read Testing Methods *---------**/
	/*---------* Generate Sequences *---------*/
	
/*	amount = 1;*/
	char seqs[amount+1][parts];
	generate_seqs(parts, amount, seqs);
/*	for (int i = 0; i < 2; i++) {*/
/*		if (i == 0) for (int j = 0; j < parts; j++) {*/
/*			seqs[i][j] = 'D';*/
/*		}*/
/*		if (i == 1) for (int j = 0; j < parts; j++) {*/
/*			seqs[i][j] = 'R';*/
/*		}*/
/*	}*/
/*	seqs[0][0] = 'C';*/
/*	seqs[0][1] = 'C';*/
/*	seqs[0][2] = 'D';*/
/*	seqs[0][3] = 'D';*/
/*	seqs[0][4] = 'C';*/
/*	seqs[0][5] = 'C';*/
/*	seqs[0][6] = 'D';*/
/*	seqs[0][7] = 'D';*/
	fgets(sorts, length, sortFile); // Get the sorting algorithms we want to test from the file
	
	fclose(sortFile);
	
	/**---------* Generate Sequences *---------**/
	
	float tCape = 0.0, tQuad = 0.0, tTim = 0.0, tQuick = 0.0, tSelection = 0.0, tBubble = 0.0,
			tBitonic = 0.0, tMerge = 0.0, tBinIns = 0.0, tHeap = 0.0, tShell = 0.0,
			tMergeIn = 0.0, tGrail = 0.0, tSqrt = 0.0, tRecStable = 0.0, tGrailDyn = 0.0,
			tShaker = 0.0;
	/*---------* Test Sequences *---------*/
	for (int seqNum = 0; seqNum < amount; seqNum++) { // For all the sequences
		/*---------* Test Sorts *---------*/
		float cape = 0.0, quad = 0.0, tim = 0.0, quick = 0.0, selection = 0.0, bubble = 0.0,
				bitonic = 0.0, merge = 0.0, binIns = 0.0, heap = 0.0, shell = 0.0,
				mergeIn = 0.0, grail = 0.0, sqrt = 0.0, recStable = 0.0, grailDyn = 0.0,
				shaker = 0.0;
		
		char capeSeq[5] = ""; // To put the sequence Cape Sort found on the main output file
		char outSamples[256] = ""; // To put the samples Cape Sort used on the main output file
		char outSort[16] = ""; // To put the sort Cape Sort chose on the main output file

		int quadCount = 0, timCount = 0, tieCount = 0;
		
		char seq[parts]; // The sequence being tested for this loop
		int j;
		for (j = 0; j < parts; j++) {
			seq[j] = seqs[seqNum][j];
		}
		seq[j] = '\0';
		printf("Sequence #%d: %s\n\n", seqNum+1, seq);
		
		/*---------* Generate Data *---------*/
		
		int* z_array, * r_array; // The arrays holding the data
		int rnd = 1;
		srand(rnd);

		z_array = malloc(max * sizeof(int)); // The array that will be sorted
		r_array = malloc(max * sizeof(int)); // The original data set
		
		generate(r_array, datanumber, unit, parts, seq);		
		
		/**---------* Generate Data *---------**/
		
		/*---------* Run Sorts *---------*/
		
		for (int repeated = 0; repeated < repeat_times; repeated++) {
			/*---------* Print Progress *---------*/ {
			
			FILE *progress = fopen("Progress.txt", "w+");
			if (progress == NULL) {
				printf("There was an error displaying the progress.");
				exit(16);
			}
			char progBuf[length+1];
			for (int i = 0; i <= length; i++) {
				progBuf[i] = '\0';
			}
			
			fprintf(progress, "Size: %d%c\n", datanumber, unit);
			fprintf(progress, "Sequence: %s, %d/%d\n", seq, seqNum+1, amount);
			fprintf(progress, "Repeat: %d/%d\n", repeated+1, repeat_times);

			float percent = ((((float) seqNum * repeat_times) + (float) repeated) / ((float) amount * (float) repeat_times)) * 100.0;
			fprintf(progress, "Percent Completion: %f%%\n", percent);
			
			double stopWatch = utime();
			double stoppedWatch = (stopWatch - start) / 1000000.0;
			fprintf(progress, "Time taken so far:");
			printTime(stoppedWatch, progress);
			
			percent /= 100;
			double left = stoppedWatch / percent * (1 - percent);
			fprintf(progress, "\nEstimated time left:");
			printTime(left, progress);
			
			fclose(progress);
			
			} /**---------* Print Progress *---------**/
			
			printf("%d: Sorting #%d %s %d%c\n", repeated+1, seqNum+1, seq, datanumber, unit);
			printf("Sorts: %s\n", sorts);
			if (strstr(sorts, "Cape") != NULL) {
				float time = test_cape(z_array, r_array, max, &quadCount, &timCount, &tieCount);
/*				float time = test_cape(z_array, r_array, max, dictionary,*/
/*						capeSeq, outSamples, outSort, repeated);*/
/*				float time = test_cape(z_array, r_array, max, smallDict, largeDict,*/
/*						capeSeq, outSamples, outSort, repeated);*/

				printf("Running Quad total: %d\nRunning Tim total: %d\nRunning Tie total: %d", quadCount, timCount, tieCount);
				printf("\n\nRan Cape %f\n", time);
				cape += time;
			}
			
			if (strstr(sorts, "Quad") != NULL) {
				float time = test_quad(z_array, r_array, max);
				printf("Ran Quad %f\n", time);
				quad += time;
			}
					
			if (strstr(sorts, "Tim") != NULL) {
				float time = test_tim(z_array, r_array, max);
				printf("Ran Tim %f\n", time);
				tim += time;
			}

			if (strstr(sorts, "Quick") != NULL) {
				float time = test_quick(z_array, r_array, max);
				printf("Ran Quick %f\n", time);
				quick += time;
			}
					
			if (strstr(sorts, "Selection") != NULL) {
				float time = test_selection(z_array, r_array, max);
				printf("Ran Selection %f\n", time);
				selection += time;
			}
					
			if (strstr(sorts, "Bubble") != NULL) {
				float time = test_bubble(z_array, r_array, max);
				printf("Ran Bubble %f\n", time);
				bubble += time;
			}
					
			if (strstr(sorts, "Bitonic") != NULL) {
				float time = test_bitonic(z_array, r_array, max);
				printf("Ran Bitonic%f\n", time);
				bitonic += time;
			}
					
			if (strstr(sorts, "Merge") != NULL) {
				float time = test_merge(z_array, r_array, max);
				printf("Ran Merge%f\n", time);
				merge += time;
			}
					
			if (strstr(sorts, "BinaryInsertion") != NULL) {
				float time = test_binary_insertion(z_array, r_array, max);
				printf("Ran Binary Insertion%f\n", time);
				binIns += time;
			}
					
			if (strstr(sorts, "Heap") != NULL) {
				float time = test_heap(z_array, r_array, max);
				printf("Ran Heap%f\n", time);
				heap += time;
			}
					
			if (strstr(sorts, "Shell") != NULL) {
				float time = test_shell(z_array, r_array, max);
				printf("Ran Shell%f\n", time);
				shell += time;
			}
					
			if (strstr(sorts, "MergeInPlace") != NULL) {
				float time = test_in_place_merge(z_array, r_array, max);
				printf("Ran Merge In Place%f\n", time);
				mergeIn += time;
			}
					
			if (strstr(sorts, "Grail") != NULL) {
				float time = test_grail(z_array, r_array, max);
				printf("Ran Grail%f\n", time);
				grail += time;
			}
					
			if (strstr(sorts, "Sqrt") != NULL) {
				float time = test_sqrt(z_array, r_array, max);
				printf("Ran Sqrt%f\n", time);
				sqrt += time;
			}
					
			if (strstr(sorts, "RecStable") != NULL) {
				float time = test_rec_stable(z_array, r_array, max);
				printf("Ran RecStable%f\n", time);
				recStable += time;
			}
					
			if (strstr(sorts, "GrailDyn") != NULL) {
				float time = test_grail_dyn_buffer(z_array, r_array, max);
				printf("Ran GrailDyn%f\n", time);
				grailDyn += time;
			}
					
			if (strstr(sorts, "Shaker") != NULL) {
				float time = test_Shaker(z_array, r_array, max);
				printf("Ran Shaker%f\n", time);
				shaker += time;
			}
			printf("\n\n");
		}
		
		/**---------* Run Sorts *---------**/
		printf("Done running sorts\n");
		
		// Free the arrays used from memory
		free(z_array);
		free(r_array);
		
		/**---------* Test Sorts *---------**/
		/*---------* Determine Fastest *---------*/
		
		float best = INT_MAX;
		char chBest[16];
		// Cape Sort is not included because it can't be in its own dictionary
		if (quad != 0.0 && quad < best) {
			best = quad;
			strcpy(chBest, "Quad");
		}
		if (tim != 0.0 && tim < best) {
			best = tim;
			strcpy(chBest, "Tim");
		}
		if (quick != 0.0 && quick < best) {
			best = quick;
			strcpy(chBest, "Quick");
		}
		if (selection != 0.0 && selection < best) {
			best = selection;
			strcpy(chBest, "Selection");
		}
		if (bubble != 0.0 && bubble < best) {
			best = bubble;
			strcpy(chBest, "Bubble");
		}
		if (bitonic != 0.0 && bitonic < best) {
			best = bitonic;
			strcpy(chBest, "Bitonic");
		}
		if (merge != 0.0 && merge < best) {
			best = merge;
			strcpy(chBest, "Merge");
		}
		if (binIns != 0.0 && binIns < best) {
			best = binIns;
			strcpy(chBest, "BinaryInsertion");
		}
		if (heap != 0.0 && heap < best) {
			best = heap;
			strcpy(chBest, "Heap");
		}
		if (shell != 0.0 && shell < best) {
			best = shell;
			strcpy(chBest, "Shell");
		}
		if (mergeIn != 0.0 && mergeIn < best) {
			best = mergeIn;
			strcpy(chBest, "Merge In Place");
		}
		if (grail != 0.0 && grail < best) {
			best = grail;
			strcpy(chBest, "Grail");
		}
		if (sqrt != 0.0 && sqrt < best) {
			best = sqrt;
			strcpy(chBest, "Sqrt");
		}
		if (recStable != 0.0 && recStable < best) {
			best = recStable;
			strcpy(chBest, "RecStable");
		}
		if (grailDyn != 0.0 && grailDyn < best) {
			best = grailDyn;
			strcpy(chBest, "GrailDyn");
		}
		if (shaker != 0.0 && shaker < best) {
			best = shaker;
			strcpy(chBest, "Shaker");
		}
		
		printf("%s is the fastest\n\n\n\n", chBest);
		
		/**---------* Determine Fastest *---------**/
		/*---------* Write Averages *---------*/
		
/*		printf("Writing Averages\n");*/
		if (cape != 0.0) {
			cape /= ((float) repeat_times);
			tCape  += cape;
			
			writeAvgCape_Test("Cape", seq, cape, quadCount, timCount, tieCount, seqTimes);
/*			writeAvgCape_Dict("Cape", outSort, seq, cape, capeSeq, outSamples, seqTimes);*/
/*			writeAvg("Cape", seq, cape, seqTimes);*/
		}
		if (quad != 0.0) {
			quad /= ((float) repeat_times);
			tQuad  += quad;
			
			writeAvg("Quad", seq, quad, seqTimes);
		}
		if (tim != 0.0) {
			tim /= ((float) repeat_times);
			tTim  += tim;
			
			writeAvg("Tim", seq, tim, seqTimes);
		}
		if (quick != 0.0) {
			quick /= ((float) repeat_times);
			tQuick  += quick;
			
			writeAvg("Quick", seq, quick, seqTimes);
		}
		if (selection != 0.0) {
			selection /= ((float) repeat_times);
			tSelection  += selection;
			
			writeAvg("Selection", seq, selection, seqTimes);
		}
		if (bubble != 0.0) {
			bubble /= ((float) repeat_times);
			tBubble  += bubble;
			
			writeAvg("Bubble", seq, bubble, seqTimes);
		}
		if (bitonic != 0.0) {
			bitonic /= ((float) repeat_times);
			tBitonic  += bitonic;
			
			writeAvg("Bitonic", seq, bitonic, seqTimes);
		}
		if (merge != 0.0) {
			merge /= ((float) repeat_times);
			tMerge  += merge;
			
			writeAvg("Merge", seq, merge, seqTimes);
		}
		if (binIns != 0.0) {
			binIns /= ((float) repeat_times);
			tBinIns  += binIns;
			
			writeAvg("Binary Insertion", seq, binIns, seqTimes);
		}
		if (heap != 0.0) {
			heap /= ((float) repeat_times);
			tHeap  += heap;
			
			writeAvg("Heap", seq, heap, seqTimes);
		}
		if (shell != 0.0) {
			shell /= ((float) repeat_times);
			tShell  += shell;
			
			writeAvg("Shell", seq, shell, seqTimes);
		}
		if (mergeIn != 0.0) {
			mergeIn /= ((float) repeat_times);
			tMergeIn  += mergeIn;
			
			writeAvg("Merge In Place", seq, mergeIn, seqTimes);
		}
		if (grail != 0.0) {
			grail /= ((float) repeat_times);
			tGrail  += grail;
			
			writeAvg("Grail", seq, grail, seqTimes);
		}
		if (sqrt != 0.0) {
			sqrt /= ((float) repeat_times);
			tSqrt  += sqrt;
			
			writeAvg("Sqrt", seq, sqrt, seqTimes);
		}
		if (recStable != 0.0) {
			recStable /= ((float) repeat_times);
			tRecStable  += recStable;
			
			writeAvg("RecStable", seq, recStable, seqTimes);
		}
		if (grailDyn != 0.0) {
			grailDyn /= ((float) repeat_times);
			tGrailDyn  += grailDyn;
			
			writeAvg("GrailDyn", seq, grailDyn, seqTimes);
		}
		if (shaker != 0.0) {
			shaker /= ((float) repeat_times);
			tShaker  += shaker;
			
			writeAvg("Shaker", seq, shaker, seqTimes);
		}
		
		// Fastest File; doesn't include Cape Sort because it can't be in its own dictionary
		if (strcmp(chBest, "Quad") == 0) {
			writeAvg("Quad", seq, quad, fastest);
		}
			
		else if (strcmp(chBest, "Tim") == 0) {
			writeAvg("Tim", seq, cape, fastest);
		}

		else if (strcmp(chBest, "Quick") == 0) {
			writeAvg("Quick", seq, quick, fastest);
		}
			
		else if (strcmp(chBest, "Selection") == 0) {
			writeAvg("Selection", seq, selection, fastest);
		}
			
		else if (strcmp(chBest, "Bubble") == 0) {
			writeAvg("Bubble", seq, bubble, fastest);
		}
			
		else if (strcmp(chBest, "Bitonic") == 0) {
			writeAvg("Bitonic", seq, bitonic, fastest);
		}
			
		else if (strcmp(chBest, "Merge") == 0) {
			writeAvg("Merge", seq, merge, fastest);
		}
			
		else if (strcmp(chBest, "BinaryInsertion") == 0) {
			writeAvg("Binary Insertion", seq, binIns, fastest);
		}
			
		else if (strcmp(chBest, "Heap") == 0) {
			writeAvg("Heap", seq, heap, fastest);
		}
			
		else if (strcmp(chBest, "Shell") == 0) {
			writeAvg("Shell", seq, shell, fastest);
		}
			
		else if (strcmp(chBest, "MergeInPlace") == 0) {
			writeAvg("Merge In Place", seq, mergeIn, fastest);
		}
			
		else if (strcmp(chBest, "Grail") == 0) {
			writeAvg("Grail", seq, grail, fastest);
		}
			
		else if (strcmp(chBest, "Sqrt") == 0) {
			writeAvg("Sqrt", seq, sqrt, fastest);
		}
			
		else if (strcmp(chBest, "RecStable") == 0) {
			writeAvg("RecStable", seq, recStable, fastest);
		}
			
		else if (strcmp(chBest, "GrailDyn") == 0) {
			writeAvg("GrailDyn", seq, grailDyn, fastest);
		}
			
		else if (strcmp(chBest, "Shaker") == 0) {
			writeAvg("Shaker", seq, shaker, fastest);
		}
		
		/**---------* Write Averages *---------**/
	}
	/**---------* Test Sequences *---------**/
	/*---------* Print Totals *---------*/
	
	if (tCape != 0.0) {
		writeAvg("Cape", "Total", tCape, seqTimes);
	}
	if (tQuad != 0.0) {
		writeAvg("Quad", "Total", tQuad, seqTimes);
	}
	if (tTim != 0.0) {
		writeAvg("Tim", "Total", tTim, seqTimes);
	}
	if (tQuick != 0.0) {
		writeAvg("Quick", "Total", tQuick, seqTimes);
	}
	if (tSelection != 0.0) {
		writeAvg("Selection", "Total", tSelection, seqTimes);
	}
	if (tBubble != 0.0) {
		writeAvg("Bubble", "Total", tBubble, seqTimes);
	}
	if (tBitonic != 0.0) {
		writeAvg("Bitonic", "Total", tBitonic, seqTimes);
	}
	if (tMerge != 0.0) {
		writeAvg("Merge", "Total", tMerge, seqTimes);
	}
	if (tBinIns != 0.0) {
		writeAvg("BinIns", "Total", tBinIns, seqTimes);
	}
	if (tHeap != 0.0) {
		writeAvg("Heap", "Total", tHeap, seqTimes);
	}
	if (tShell != 0.0) {
		writeAvg("Shell", "Total", tShell, seqTimes);
	}
	if (tMergeIn != 0.0) {
		writeAvg("MergeIn", "Total", tMergeIn, seqTimes);
	}
	if (tGrail != 0.0) {
		writeAvg("Grail", "Total", tGrail, seqTimes);
	}
	if (tSqrt != 0.0) {
		writeAvg("Sqrt", "Total", tSqrt, seqTimes);
	}
	if (tRecStable != 0.0) {
		writeAvg("RecStable", "Total", tRecStable, seqTimes);
	}
	if (tGrailDyn != 0.0) {
		writeAvg("GrailDyn", "Total", tGrailDyn, seqTimes);
	}
	if (tShaker != 0.0) {
		writeAvg("Shaker", "Total", tShaker, seqTimes);
	}
	/**---------* Print Totals *---------**/
	/*---------* Close Out Program *---------*/
	
	// Close the open csv files
/*	fclose(dictionary);*/
/*	fclose(smallDict);*/
/*	fclose(largeDict);*/
	fclose(seqTimes);
	fclose(fastest);
	
	// Stop the timer
	double end = utime();
	double total = (end - start) / 1000000.0;
	
	// The file that appears when the testing for the size is complete
	char closeName[28] = "Times/TestComplete_";
	strcat(closeName, chNumber);
	strcat(closeName, chUnit);
	strcat(closeName, ".txt");
	printf("\n%s\n", closeName);
	FILE *done = fopen(closeName, "w+");
	
	// Print the time on timer
	printf("Task completion time:");
	fprintf(done, "Task completion time:");
	
	printTime(total, stdout);
	printTime(total, done);
	
	fclose(done);
	} // This closes the multiTest loop
    return 0;
	
	/**---------* Close Out Program *---------**/
}
