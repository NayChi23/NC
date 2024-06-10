#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COLS 7
#define MAX_ROWS 2 //200 for the estrus and it will take 18 round to get one data which is equalivalent to 4 hours
#define MAX_FIELD_LENGTH 50
#define MAX_SIZE 15

// Define the node structure for a doubly linked list
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to print the list from the given node to the end
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}
// Function to delete every node in the list
void deleteList(struct Node** head) {
    struct Node* temp = *head;
    struct Node* nextNode;

    while (temp != NULL) {
        nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }

    *head = NULL;
}

struct CircularQueue {
    int* arr; // Array to store queue elements
    int front, rear; // Front and rear pointers
    int capacity; // Maximum capacity of the queue
    int size; // Current number of elements in the queue
};

struct CircularQueue* createQueue(int capacity) {
    struct CircularQueue* queue = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    queue->arr = (int*)malloc(capacity * sizeof(int));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->size = 0;
    return queue;
}
int isEmpty(struct CircularQueue* queue) {
    return queue->size == 0;
}

void enqueue(struct CircularQueue* queue, int item) {
    if (isEmpty(queue))
        queue->front = 0;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->arr[queue->rear] = item;
    queue->size++;
    //printf("%d enqueued to queue\n", item);
}

int dequeue(struct CircularQueue* queue) {
    int item = queue->arr[queue->front];
    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

void printQueue(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Elements of the queue are: ");
    int i = queue->front;
    do {
        printf("%d ", queue->arr[i]);
        i = (i + 1) % queue->capacity;
    } while (i != (queue->rear + 1) % queue->capacity);
    printf("\n");
}
int indexFinding(struct CircularQueue* queue, int no){
    int i = queue->front;
    int count = 0;
    while (count <queue->size)
    {
        if(count == no)
        {
            return queue->arr[i];
            break;
        }
        i = (i + 1) % queue->capacity;
        count++;
    }
    
}
int Estreus(float,float,float,float,float,float);
int CompareData(struct CircularQueue* queue);

int main(){
    unsigned int numberZero =0; 
    unsigned long int numberOne =0;  //Store how many 1's in the data
    unsigned int num=0;
    bool FirstTurn = 1; // if there is already 15 data or not 
    unsigned int check_fifteen_cycle = 0;
    struct Node* result_data = NULL;


    struct CircularQueue* total_one_cycle_count = createQueue(MAX_SIZE);
    while(1){
        char field[MAX_ROWS][MAX_COLS][MAX_FIELD_LENGTH] = {
            {"15:34:52,-0.10,0.01,0.86,50.88,-10.02,-4.12"},
            {"15:34:52,-0.05,-0.17,0.79,-21.53,-23.01,21.22"}
        };

        if(num == 18 && FirstTurn  == 1){
            enqueue(total_one_cycle_count,numberOne);
            printf("the total number one is %d\n", numberOne);
            numberOne = 0 ;
            numberZero = 0 ;
            num = 0;
            check_fifteen_cycle += 1;
            printf("Complete %d turn \n", check_fifteen_cycle);
            //printQueue(total_one_cycle_count);
            
            if(check_fifteen_cycle == 15)
            {
                FirstTurn = 0;
                printf("The result of compared data is\t%d\n",CompareData(total_one_cycle_count));
                if(CompareData(total_one_cycle_count) != -1){
                    insertAtEnd(&result_data, CompareData(total_one_cycle_count));
                }
            }
            
        }
        else if(num == 18 && FirstTurn  == 0){
            dequeue(total_one_cycle_count);
            //printQueue(total_one_cycle_count);
            enqueue(total_one_cycle_count,numberOne);
            check_fifteen_cycle +=1;
            printf("Complete %d turn \n", check_fifteen_cycle);
            printf("The result of compared data is\t%d\n",CompareData(total_one_cycle_count));
            numberOne = 0 ;
            numberZero = 0 ;
            num = 0;
            if(CompareData(total_one_cycle_count) != -1){
                    insertAtEnd(&result_data, CompareData(total_one_cycle_count));
            }
            printf("Doubly linked list: ");
            printList(result_data);
            break;
        }
        else{
            unsigned int row = 0, col = 0, b=0;

        char tempoarray[MAX_COLS][MAX_FIELD_LENGTH];
        while(row<MAX_ROWS && field[row][0][0] != '\0'){
            col = 0; // Reset col for each row
            char* token = strtok(field[row][col], ",");
            
            while (token != NULL && col < MAX_COLS) {
                strcpy(tempoarray[col], token);
                token = strtok(NULL, ",");
                col +=1;
            }
            // Display the items in the row
            /*for (b = 0; b < col; b++) {
                printf("%s\t", tempoarray[b]);
            }
            printf("\n"); // Newline after each row
            */
            row++;
            float ax,ay,az,gx,gy,gz;
            ax = atof(tempoarray[1]);
            ay = atof(tempoarray[2]);
            az = atof(tempoarray[3]);
            gx = atof(tempoarray[4]);
            gy = atof(tempoarray[5]);
            gz = atof(tempoarray[6]);
            //printf("%.2f %.2f %.2f %.2f %.2f %.2f\n",ax,ay,az,gx,gy,gz);
            //printf("%d\n",Estreus(ax,ay,az,gx,gy,gz));
            if (Estreus(ax,ay,az,gx,gy,gz)==1)
            {
                numberOne = numberOne +1;
            }
            else{
                numberZero = numberZero +1;
            }
            
        }
        num +=1;
        //printf("row number is %u\n",row);
        //printf("the total loop number is %u\n",num);
        }
        

    }
    return 0;
}
int CompareData(struct CircularQueue* q){
    //Check average total sum of the first 12 data
    long int sum = 0;
    long avg_num = 0;
    for(int i=0;i<12;i++){
        sum = sum + indexFinding(q,i);
    }   
    avg_num = sum/12;

    if (avg_num > indexFinding(q,13)) {
        return -1; // which need to skip the data that means (delet the first one and continue for getting data)
    }
    else {
    if (indexFinding(q,13) < indexFinding(q,14) && indexFinding(q,14) < indexFinding(q,15)) {
        //printf("Detected\n");
        return 1;
    } else if (indexFinding(q,13) < indexFinding(q,14)) {
        //printf("Warning\n");
        return 0;
    } else {
        //printf("Heat not detected\n");
        return 2;
    }
    }
}
int Estreus(float Ax,float Ay,float Az,float Gx,float Gy,float Gz )
{
    float AxXGx = Ax*Gx,AyXAz = Ay*Az,AxXGy = Ax*Gy,AxXGz = Ax*Gz,AxXAy = Ax*Ay,AxXAz = Ax*Az,AyXAx = Ay*Ax,AyXGx = Ay*Gx,AyXGy=Ay*Gy,AyXGz = Ay*Gz,AzXAx = Az*Ax,AzXAy = Az*Ay,AzXGx = Az*Gx,AzxGy = Az*Gy,AzXGz =Az*Gz,Ax_squared = Ax*Ax, Ay_squared = Ay*Ay, Az_squared = Az*Az,Gx_squared = Gx*Gx, Gy_squared = Gy*Gy, Gz_squared = Gz*Gz,GxXGz=Gx*Gz,GxXGy=Gx*Gy,GyXGz=Gy*Gz,AzXGy=Az*Gy;
	if ( Gx_squared <= 0.71) {
		if ( Gy <= 0.56) {
			if ( Gx_squared <= 0.07) {
				if ( Gx <= 0.4) {
					if ( Gy <= -0.49) {
						if ( Gx <= -0.42) {
							if ( Gx <= -0.83) {
								if ( Gz <= -1.28) {
									if ( GxXGy <= 0.44) {
										return 1;
									}
									else {
										return 0;
									}
								}
								else {
									if ( Az <= -0.27) {
										if ( AxXGy <= 0.3) {
											if ( Gx_squared <= -0.06) {
												return 1;
											}
											else {
												if ( Gx <= -1.05) {
													if ( AyXAz <= 0.2) {
														if ( AzXGx <= 0.52) {
															if ( Az <= -0.68) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( AyXGx <= -0.46) {
														return 1;
													}
													else {
														if ( GxXGz <= 0.02) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
											}
										}
										else {
											return 1;
										}
									}
									else {
										if ( AyXGx <= 0.31) {
											if ( Ax <= -0.01) {
												if ( AxXGx <= -0.01) {
													return 1;
												}
												else {
													return 1;
												}
											}
											else {
												if ( AzXGx <= 0.26) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( AyXGz <= -0.12) {
												return 0;
											}
											else {
												if ( Az_squared <= -0.18) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
									}
								}
							}
							else {
								if ( AxXAz <= 0.32) {
									if ( GxXGy <= 0.28) {
										if ( Gy_squared <= 0.63) {
											if ( Gy_squared <= -0.05) {
												if ( GxXGz <= -0.17) {
													return 0;
												}
												else {
													if ( AxXGy <= -0.12) {
														if ( Ax_squared <= 0.08) {
															if ( Ax <= 0.48) {
																if ( Ax_squared <= -0.06) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
													else {
														if ( AyXGz <= 0.55) {
															if ( GyXGz <= 0.03) {
																if ( Ay <= -0.52) {
																	if ( GyXGz <= -0.1) {
																		return 0;
																	}
																	else {
																		if ( GyXGz <= 0.0) {
																			if ( Gx <= -0.74) {
																				return 0;
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																}
																else {
																	if ( AzXGy <= 0.21) {
																		if ( Gz <= 0.23) {
																			if ( GxXGy <= 0.09) {
																				return 1;
																			}
																			else {
																				if ( AzXGz <= -0.02) {
																					return 0;
																				}
																				else {
																					return 1;
																				}
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		return 1;
																	}
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
												}
											}
											else {
												if ( Gx_squared <= -0.09) {
													if ( Ax_squared <= -0.01) {
														if ( AzXGx <= 0.09) {
															if ( Gz <= -0.32) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															if ( GyXGz <= 0.31) {
																if ( AyXGx <= 0.27) {
																	if ( AxXAy <= 0.1) {
																		if ( GxXGy <= 0.14) {
																			return 0;
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		if ( AxXAz <= -0.09) {
																			return 1;
																		}
																		else {
																			if ( Ay <= -0.62) {
																				return 1;
																			}
																			else {
																				if ( AyXAz <= -0.54) {
																					return 1;
																				}
																				else {
																					return 1;
																				}
																			}
																		}
																	}
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( Gy <= -1.01) {
														return 1;
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											return 0;
										}
									}
									else {
										if ( Gz <= -0.74) {
											if ( AyXGy <= 0.95) {
												return 1;
											}
											else {
												if ( Gy <= -2.32) {
													return 0;
												}
												else {
													if ( Gz_squared <= 0.7) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											if ( Gx_squared <= -0.09) {
												return 1;
											}
											else {
												return 1;
											}
										}
									}
								}
								else {
									return 1;
								}
							}
						}
						else {
							if ( Gx_squared <= -0.16) {
								if ( Gx_squared <= -0.16) {
									if ( Gz <= 0.34) {
										if ( Gz <= -1.23) {
											if ( AyXGy <= 1.9) {
												if ( GxXGz <= 0.03) {
													if ( Gy <= -1.12) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( GyXGz <= 0.06) {
												if ( Gz <= -0.18) {
													if ( AxXGy <= 0.03) {
														if ( Gz_squared <= -0.12) {
															if ( AyXAz <= 0.0) {
																if ( Gy <= -0.77) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Gx <= -0.06) {
																	return 1;
																}
																else {
																	if ( Gz <= -0.24) {
																		return 1;
																	}
																	else {
																		return 0;
																	}
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( GxXGz <= 0.01) {
														if ( Ay <= 0.19) {
															if ( AzXGx <= 0.04) {
																if ( AyXAz <= -0.05) {
																	return 1;
																}
																else {
																	if ( AyXGx <= -0.0) {
																		if ( AxXAy <= -0.18) {
																			return 1;
																		}
																		else {
																			return 0;
																		}
																	}
																	else {
																		if ( AyXGz <= -0.04) {
																			return 0;
																		}
																		else {
																			return 0;
																		}
																	}
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( Az <= -0.04) {
																if ( GxXGz <= 0.01) {
																	if ( AzXGy <= 0.2) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gx_squared <= -0.17) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( AyXGy <= -0.5) {
													return 1;
												}
												else {
													if ( AxXGy <= -0.14) {
														return 1;
													}
													else {
														if ( Gy <= -1.06) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
											}
										}
									}
									else {
										if ( AyXGz <= -0.12) {
											if ( Ax_squared <= -0.03) {
												if ( Gy <= -0.78) {
													return 0;
												}
												else {
													if ( Gz <= 0.76) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( Gx_squared <= -0.17) {
													return 1;
												}
												else {
													if ( Gx_squared <= -0.17) {
														return 1;
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( Gy <= -1.92) {
												return 1;
											}
											else {
												if ( GyXGz <= -0.57) {
													return 1;
												}
												else {
													if ( GxXGy <= -0.01) {
														if ( AyXGx <= 0.06) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														if ( Gz_squared <= -0.08) {
															if ( AxXGy <= 0.02) {
																if ( Az_squared <= -0.09) {
																	if ( Gz <= 0.6) {
																		return 0;
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( GyXGz <= -0.24) {
																return 0;
															}
															else {
																if ( GxXGz <= 0.02) {
																	if ( Az_squared <= 0.35) {
																		if ( AxXGy <= -0.21) {
																			return 1;
																		}
																		else {
																			if ( AyXAz <= -0.09) {
																				if ( AzXGz <= -0.09) {
																					if ( AyXAz <= -0.53) {
																						return 0;
																					}
																					else {
																						if ( AxXGy <= 0.03) {
																							if ( GyXGz <= -0.19) {
																								if ( Gy_squared <= -0.04) {
																									return 0;
																								}
																								else {
																									return 0;
																								}
																							}
																							else {
																								return 0;
																							}
																						}
																						else {
																							return 0;
																						}
																					}
																				}
																				else {
																					if ( Gx_squared <= -0.17) {
																						if ( Gz <= 0.76) {
																							if ( Gz <= 0.73) {
																								return 0;
																							}
																							else {
																								return 0;
																							}
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
										}
									}
								}
								else {
									if ( GxXGy <= -0.1) {
										return 1;
									}
									else {
										if ( Gz <= -0.07) {
											if ( AxXAy <= -0.21) {
												if ( Gx <= -0.01) {
													return 1;
												}
												else {
													return 1;
												}
											}
											else {
												if ( Gz <= -0.22) {
													if ( Gx_squared <= -0.16) {
														if ( Ay <= 0.58) {
															return 1;
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( Gx <= 0.01) {
												if ( AxXGy <= -0.07) {
													if ( AxXGx <= -0.09) {
														return 1;
													}
													else {
														if ( Ay <= 0.0) {
															return 0;
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( Gx_squared <= -0.16) {
														if ( Gy <= -1.13) {
															return 1;
														}
														else {
															if ( AyXGy <= -0.56) {
																return 0;
															}
															else {
																if ( Gx <= -0.22) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( GxXGz <= 0.03) {
													if ( GxXGy <= -0.05) {
														return 1;
													}
													else {
														if ( Gz_squared <= -0.15) {
															return 1;
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( AyXGz <= -0.47) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
										}
									}
								}
							}
							else {
								if ( Gz <= -1.01) {
									if ( AxXGx <= 0.02) {
										if ( Ay <= 0.75) {
											return 1;
										}
										else {
											return 1;
										}
									}
									else {
										if ( Ay <= 0.92) {
											return 1;
										}
										else {
											return 1;
										}
									}
								}
								else {
									if ( GxXGy <= -0.08) {
										if ( AyXGx <= -0.04) {
											if ( AxXGx <= -0.03) {
												return 0;
											}
											else {
												if ( Ax_squared <= 0.09) {
													if ( Gz <= 0.39) {
														if ( AxXAy <= -0.49) {
															return 1;
														}
														else {
															if ( GxXGy <= -0.16) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( AzXGx <= -0.08) {
												return 1;
											}
											else {
												return 1;
											}
										}
									}
									else {
										if ( Ax <= 0.06) {
											if ( AxXGy <= 0.24) {
												if ( GyXGz <= 0.09) {
													if ( AzXGx <= -0.13) {
														return 1;
													}
													else {
														if ( Gx <= -0.29) {
															if ( GxXGz <= -0.05) {
																return 0;
															}
															else {
																if ( Ax <= -0.57) {
																	if ( Gz <= 0.09) {
																		return 1;
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	if ( Gz_squared <= -0.1) {
																		if ( Gy_squared <= -0.04) {
																			if ( Gy <= -0.75) {
																				return 0;
																			}
																			else {
																				if ( AxXGy <= -0.06) {
																					return 1;
																				}
																				else {
																					return 1;
																				}
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		return 0;
																	}
																}
															}
														}
														else {
															if ( GyXGz <= -0.2) {
																return 0;
															}
															else {
																if ( AzXGz <= 0.04) {
																	if ( GyXGz <= -0.14) {
																		return 0;
																	}
																	else {
																		if ( Gx <= 0.01) {
																			return 1;
																		}
																		else {
																			if ( GyXGz <= -0.02) {
																				if ( Gy_squared <= -0.07) {
																					if ( Ax_squared <= -0.09) {
																						if ( AxXGz <= -0.0) {
																							return 1;
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																}
																else {
																	if ( Ay_squared <= -0.08) {
																		return 1;
																	}
																	else {
																		return 0;
																	}
																}
															}
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
										else {
											if ( Az <= 0.12) {
												if ( AyXGy <= -0.21) {
													if ( AxXAz <= -0.25) {
														return 1;
													}
													else {
														if ( AzXGx <= -0.01) {
															return 1;
														}
														else {
															if ( AxXGz <= -0.12) {
																return 1;
															}
															else {
																if ( AxXGx <= -0.06) {
																	if ( AxXAz <= -0.16) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( Gx <= 0.15) {
														return 0;
													}
													else {
														if ( AzXGy <= 0.16) {
															return 0;
														}
														else {
															if ( AxXAy <= -0.84) {
																return 1;
															}
															else {
																if ( Az_squared <= 0.3) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												if ( Ay_squared <= -0.31) {
													return 1;
												}
												else {
													if ( Gz <= 0.55) {
														if ( GyXGz <= 0.06) {
															if ( GxXGy <= 0.05) {
																if ( Az <= 0.41) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
											}
										}
									}
								}
							}
						}
					}
					else {
						if ( Ay <= -0.46) {
							if ( AyXGz <= -0.24) {
								if ( AxXGy <= 0.06) {
									if ( Gx_squared <= -0.1) {
										if ( GxXGz <= 0.01) {
											if ( Ax <= 1.19) {
												if ( Gx_squared <= -0.12) {
													if ( Gx <= -0.1) {
														if ( AxXAy <= -0.35) {
															if ( AyXGy <= 0.28) {
																if ( AzXGy <= 0.02) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( Ay <= -0.9) {
																return 1;
															}
															else {
																if ( Ay_squared <= -0.23) {
																	return 0;
																}
																else {
																	if ( AyXGx <= 0.23) {
																		if ( Gz_squared <= -0.05) {
																			if ( Ax <= -0.1) {
																				if ( GyXGz <= -0.05) {
																					return 0;
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																		else {
																			if ( GyXGz <= -0.01) {
																				if ( Gy <= -0.05) {
																					if ( GxXGz <= -0.04) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																	else {
																		return 0;
																	}
																}
															}
														}
													}
													else {
														if ( Gy <= 0.07) {
															if ( Az <= -0.19) {
																return 0;
															}
															else {
																if ( AyXGz <= -0.34) {
																	if ( Ay <= -0.83) {
																		return 0;
																	}
																	else {
																		if ( AyXGz <= -0.48) {
																			return 0;
																		}
																		else {
																			return 0;
																		}
																	}
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( Ay <= -0.81) {
														return 0;
													}
													else {
														if ( AxXGx <= -0.2) {
															return 0;
														}
														else {
															if ( Gy <= -0.14) {
																return 0;
															}
															else {
																if ( Ay_squared <= -0.13) {
																	return 0;
																}
																else {
																	if ( GyXGz <= -0.02) {
																		return 0;
																	}
																	else {
																		return 0;
																	}
																}
															}
														}
													}
												}
											}
											else {
												if ( Ay <= -0.87) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( GyXGz <= -0.08) {
												if ( AxXGx <= 0.09) {
													if ( Gy_squared <= -0.16) {
														if ( AyXGz <= -0.38) {
															if ( Az_squared <= 0.07) {
																if ( Gz_squared <= 0.03) {
																	if ( Ay_squared <= -0.07) {
																		return 0;
																	}
																	else {
																		if ( Ay <= -0.83) {
																			return 0;
																		}
																		else {
																			return 0;
																		}
																	}
																}
																else {
																	if ( Gy_squared <= -0.17) {
																		return 0;
																	}
																	else {
																		return 0;
																	}
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( AyXAz <= 0.54) {
															if ( AyXGy <= 0.32) {
																if ( Gz_squared <= -0.07) {
																	return 0;
																}
																else {
																	if ( Gz <= 0.92) {
																		return 0;
																	}
																	else {
																		if ( AzXGz <= -0.29) {
																			return 0;
																		}
																		else {
																			if ( Ax_squared <= -0.01) {
																				return 0;
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( Gy <= 0.18) {
													if ( Gz_squared <= -0.05) {
														if ( Gz_squared <= -0.06) {
															if ( AzXGz <= -0.02) {
																return 0;
															}
															else {
																return 1;
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( Gz_squared <= 0.16) {
															if ( AyXGy <= 0.07) {
																if ( AyXGy <= 0.05) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AzXGx <= -0.04) {
																	return 0;
																}
																else {
																	if ( Ax <= -0.22) {
																		return 0;
																	}
																	else {
																		return 0;
																	}
																}
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( Az <= -0.69) {
														return 1;
													}
													else {
														if ( AyXGz <= -0.49) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
											}
										}
									}
									else {
										if ( Gz <= 1.3) {
											if ( Gy_squared <= -0.17) {
												if ( Ay <= -0.91) {
													return 1;
												}
												else {
													if ( AxXGz <= 0.35) {
														if ( Gz <= 1.1) {
															if ( AyXGz <= -0.3) {
																if ( AyXGy <= 0.12) {
																	if ( AzXGz <= -0.32) {
																		return 0;
																	}
																	else {
																		if ( AyXGx <= 0.52) {
																			if ( Gz <= 0.96) {
																				if ( AxXAy <= -0.62) {
																					return 0;
																				}
																				else {
																					if ( Gy <= 0.21) {
																						if ( Gx <= -0.91) {
																							if ( Gx_squared <= -0.01) {
																								if ( GxXGz <= -0.14) {
																									return 0;
																								}
																								else {
																									return 0;
																								}
																							}
																							else {
																								return 0;
																							}
																						}
																						else {
																							if ( AxXGx <= 0.02) {
																								if ( Ax <= 0.87) {
																									return 0;
																								}
																								else {
																									return 0;
																								}
																							}
																							else {
																								if ( Ay <= -0.8) {
																									return 0;
																								}
																								else {
																									return 0;
																								}
																							}
																						}
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																		else {
																			return 0;
																		}
																	}
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( Gy_squared <= -0.15) {
													if ( Gx <= -0.96) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											return 0;
										}
									}
								}
								else {
									if ( Ax <= -0.8) {
										return 0;
									}
									else {
										if ( AxXAz <= -0.26) {
											return 1;
										}
										else {
											if ( GxXGz <= -0.08) {
												if ( Ax <= 0.98) {
													return 0;
												}
												else {
													return 1;
												}
											}
											else {
												if ( Ax_squared <= 0.19) {
													if ( AxXAz <= -0.05) {
														return 0;
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
										}
									}
								}
							}
							else {
								if ( Gy_squared <= -0.17) {
									if ( AxXGz <= 0.03) {
										if ( Gx_squared <= -0.15) {
											if ( Az <= 1.16) {
												if ( AyXAz <= 0.14) {
													if ( AyXGx <= -0.02) {
														if ( Gz <= -0.29) {
															if ( Ax <= 0.13) {
																if ( AzXGx <= 0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Gx <= 0.12) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( Gx <= 0.13) {
																if ( AxXAy <= 0.24) {
																	if ( AxXAy <= -0.69) {
																		return 1;
																	}
																	else {
																		if ( Gx_squared <= -0.16) {
																			if ( Gx <= 0.1) {
																				if ( AxXAy <= -0.03) {
																					if ( Ax <= 0.43) {
																						if ( AzXGy <= -0.02) {
																							return 0;
																						}
																						else {
																							if ( Gz_squared <= -0.15) {
																								return 0;
																							}
																							else {
																								return 0;
																							}
																						}
																					}
																					else {
																						if ( AzXGy <= -0.01) {
																							if ( Gx <= 0.08) {
																								return 1;
																							}
																							else {
																								return 0;
																							}
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																				else {
																					if ( Gx <= 0.04) {
																						return 0;
																					}
																					else {
																						if ( Ax <= -0.28) {
																							if ( Gx_squared <= -0.17) {
																								if ( AxXGz <= -0.01) {
																									return 1;
																								}
																								else {
																									return 1;
																								}
																							}
																							else {
																								return 0;
																							}
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																}
																else {
																	if ( GxXGy <= 0.01) {
																		if ( Az_squared <= -0.21) {
																			return 0;
																		}
																		else {
																			return 0;
																		}
																	}
																	else {
																		return 0;
																	}
																}
															}
															else {
																if ( Az_squared <= -0.21) {
																	if ( Gy <= 0.04) {
																		if ( AyXGz <= 0.13) {
																			if ( AzXGy <= -0.01) {
																				if ( Gx <= 0.16) {
																					return 0;
																				}
																				else {
																					if ( GxXGz <= -0.0) {
																						return 0;
																					}
																					else {
																						return 1;
																					}
																				}
																			}
																			else {
																				if ( Az <= 0.61) {
																					return 1;
																				}
																				else {
																					return 1;
																				}
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		if ( AzXGx <= 0.01) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																}
																else {
																	if ( AxXAz <= 0.1) {
																		if ( Ax <= 1.53) {
																			return 0;
																		}
																		else {
																			return 0;
																		}
																	}
																	else {
																		return 1;
																	}
																}
															}
														}
													}
													else {
														if ( AxXGy <= -0.04) {
															if ( Gx_squared <= -0.16) {
																if ( Ax_squared <= 0.05) {
																	return 0;
																}
																else {
																	if ( AyXAz <= -0.08) {
																		return 1;
																	}
																	else {
																		return 0;
																	}
																}
															}
															else {
																if ( AxXAy <= -0.54) {
																	return 0;
																}
																else {
																	if ( AyXGz <= 0.08) {
																		return 0;
																	}
																	else {
																		if ( GxXGy <= 0.02) {
																			return 0;
																		}
																		else {
																			return 0;
																		}
																	}
																}
															}
														}
														else {
															if ( AxXGy <= 0.03) {
																if ( AyXGz <= 0.2) {
																	if ( Ax <= -0.26) {
																		if ( Gz_squared <= -0.15) {
																			if ( AxXAy <= 0.05) {
																				return 1;
																			}
																			else {
																				if ( Gy <= -0.02) {
																					if ( GxXGy <= 0.01) {
																						return 0;
																					}
																					else {
																						return 1;
																					}
																				}
																				else {
																					if ( AxXAy <= 0.13) {
																						return 0;
																					}
																					else {
																						if ( Ay_squared <= -0.04) {
																							return 0;
																						}
																						else {
																							if ( Az_squared <= -0.21) {
																								return 0;
																							}
																							else {
																								return 0;
																							}
																						}
																					}
																				}
																			}
																		}
																		else {
																			if ( GxXGz <= -0.01) {
																				return 1;
																			}
																			else {
																				if ( AzXGz <= 0.02) {
																					if ( AxXAy <= 0.14) {
																						if ( Az_squared <= -0.22) {
																							return 0;
																						}
																						else {
																							if ( Ax <= -0.41) {
																								return 0;
																							}
																							else {
																								return 1;
																							}
																						}
																					}
																					else {
																						if ( AzXGz <= 0.0) {
																							return 0;
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																				else {
																					return 1;
																				}
																			}
																		}
																	}
																	else {
																		if ( AyXGz <= -0.1) {
																			return 1;
																		}
																		else {
																			if ( GxXGz <= 0.0) {
																				return 0;
																			}
																			else {
																				if ( AxXGy <= 0.03) {
																					if ( Gz <= 0.05) {
																						if ( AyXGz <= 0.09) {
																							if ( Gx <= -0.18) {
																								return 0;
																							}
																							else {
																								if ( AyXGy <= 0.02) {
																									if ( AxXGz <= -0.03) {
																										return 0;
																									}
																									else {
																										if ( AxXAy <= -0.21) {
																											if ( Az <= 0.88) {
																												return 0;
																											}
																											else {
																												return 0;
																											}
																										}
																										else {
																											return 0;
																										}
																									}
																								}
																								else {
																									if ( GxXGz <= 0.0) {
																										return 0;
																									}
																									else {
																										if ( Gx <= -0.05) {
																											return 0;
																										}
																										else {
																											return 0;
																										}
																									}
																								}
																							}
																						}
																						else {
																							if ( GxXGz <= 0.01) {
																								return 0;
																							}
																							else {
																								if ( AxXGy <= 0.01) {
																									if ( Gz_squared <= -0.15) {
																										if ( GyXGz <= -0.03) {
																											return 0;
																										}
																										else {
																											return 0;
																										}
																									}
																									else {
																										if ( AzXGy <= -0.01) {
																											return 0;
																										}
																										else {
																											return 0;
																										}
																									}
																								}
																								else {
																									return 0;
																								}
																							}
																						}
																					}
																					else {
																						if ( AzXGz <= 0.02) {
																							if ( Az <= 0.58) {
																								return 0;
																							}
																							else {
																								return 0;
																							}
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																				else {
																					return 1;
																				}
																			}
																		}
																	}
																}
																else {
																	if ( AxXGz <= -0.05) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
															}
															else {
																if ( AzXGz <= 0.0) {
																	return 0;
																}
																else {
																	if ( Gy_squared <= -0.18) {
																		if ( Ay_squared <= -0.03) {
																			return 0;
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		if ( AzXGx <= 0.03) {
																			if ( AxXAy <= -0.61) {
																				return 1;
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																}
															}
														}
													}
												}
												else {
													if ( Ax <= 0.65) {
														if ( Az_squared <= 0.13) {
															if ( Az_squared <= -0.05) {
																if ( AxXAz <= -0.08) {
																	if ( AxXGz <= -0.08) {
																		return 1;
																	}
																	else {
																		if ( AyXAz <= 0.41) {
																			if ( Gx <= -0.04) {
																				return 1;
																			}
																			else {
																				return 0;
																			}
																		}
																		else {
																			return 0;
																		}
																	}
																}
																else {
																	if ( Ay <= -0.66) {
																		if ( AyXAz <= 0.17) {
																			if ( GyXGz <= -0.04) {
																				if ( AxXAy <= 0.26) {
																					if ( Az <= 0.34) {
																						return 1;
																					}
																					else {
																						return 1;
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				if ( AxXGx <= -0.03) {
																					return 0;
																				}
																				else {
																					if ( AzXGy <= -0.0) {
																						if ( AyXGy <= 0.05) {
																							if ( Ax <= -0.18) {
																								if ( Gx <= 0.09) {
																									return 0;
																								}
																								else {
																									return 0;
																								}
																							}
																							else {
																								return 0;
																							}
																						}
																						else {
																							return 1;
																						}
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																		}
																		else {
																			if ( Az_squared <= -0.17) {
																				if ( Gz_squared <= -0.15) {
																					if ( Gz <= 0.07) {
																						if ( AxXAy <= 0.27) {
																							if ( Gz_squared <= -0.15) {
																								if ( AxXAz <= 0.05) {
																									if ( Ax_squared <= -0.06) {
																										if ( AyXGx <= 0.05) {
																											if ( AyXGz <= 0.04) {
																												if ( AyXGz <= 0.01) {
																													return 0;
																												}
																												else {
																													return 0;
																												}
																											}
																											else {
																												return 0;
																											}
																										}
																										else {
																											return 0;
																										}
																									}
																									else {
																										return 0;
																									}
																								}
																								else {
																									if ( Ax_squared <= -0.11) {
																										if ( AzXGy <= -0.04) {
																											return 0;
																										}
																										else {
																											if ( Gy <= -0.02) {
																												return 0;
																											}
																											else {
																												return 0;
																											}
																										}
																									}
																									else {
																										return 1;
																									}
																								}
																							}
																							else {
																								return 0;
																							}
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						if ( Az <= 0.27) {
																							if ( Az <= 0.21) {
																								return 0;
																							}
																							else {
																								return 0;
																							}
																						}
																						else {
																							if ( AyXGz <= -0.07) {
																								return 1;
																							}
																							else {
																								return 0;
																							}
																						}
																					}
																				}
																				else {
																					if ( Gx <= -0.12) {
																						return 0;
																					}
																					else {
																						if ( Gx <= 0.0) {
																							return 0;
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																			}
																			else {
																				if ( Ay <= -0.67) {
																					if ( Ax <= -0.9) {
																						if ( AxXGz <= -0.04) {
																							return 1;
																						}
																						else {
																							if ( GxXGz <= 0.01) {
																								return 0;
																							}
																							else {
																								return 0;
																							}
																						}
																					}
																					else {
																						if ( Az_squared <= -0.15) {
																							if ( AzXGy <= 0.0) {
																								if ( Gx <= 0.21) {
																									if ( Gy <= 0.21) {
																										if ( AzXGz <= 0.06) {
																											if ( AxXAy <= -0.28) {
																												return 0;
																											}
																											else {
																												if ( Az_squared <= -0.15) {
																													if ( AyXAz <= 0.23) {
																														return 0;
																													}
																													else {
																														if ( Ay_squared <= 0.03) {
																															if ( Ay_squared <= -0.04) {
																																if ( Ay_squared <= -0.07) {
																																	return 0;
																																}
																																else {
																																	return 0;
																																}
																															}
																															else {
																																if ( Ay <= -0.76) {
																																	return 0;
																																}
																																else {
																																	if ( Gy_squared <= -0.18) {
																																		return 0;
																																	}
																																	else {
																																		return 0;
																																	}
																																}
																															}
																														}
																														else {
																															if ( AzXGx <= -0.01) {
																																return 0;
																															}
																															else {
																																if ( AzXGy <= -0.02) {
																																	return 0;
																																}
																																else {
																																	return 0;
																																}
																															}
																														}
																													}
																												}
																												else {
																													if ( AyXGx <= 0.1) {
																														if ( AyXGx <= 0.02) {
																															if ( GxXGy <= 0.01) {
																																if ( Gz <= 0.03) {
																																	return 0;
																																}
																																else {
																																	return 0;
																																}
																															}
																															else {
																																return 0;
																															}
																														}
																														else {
																															return 0;
																														}
																													}
																													else {
																														return 0;
																													}
																												}
																											}
																										}
																										else {
																											return 0;
																										}
																									}
																									else {
																										if ( Gx <= 0.05) {
																											if ( AzXGx <= 0.01) {
																												return 0;
																											}
																											else {
																												if ( AyXGz <= -0.06) {
																													return 0;
																												}
																												else {
																													return 0;
																												}
																											}
																										}
																										else {
																											return 0;
																										}
																									}
																								}
																								else {
																									if ( AxXGx <= -0.01) {
																										return 0;
																									}
																									else {
																										return 0;
																									}
																								}
																							}
																							else {
																								if ( Gx_squared <= -0.17) {
																									return 0;
																								}
																								else {
																									if ( AyXAz <= 0.27) {
																										if ( AzXGz <= 0.07) {
																											if ( AxXGz <= 0.0) {
																												if ( GxXGz <= 0.01) {
																													if ( AyXGz <= 0.01) {
																														return 0;
																													}
																													else {
																														return 0;
																													}
																												}
																												else {
																													return 0;
																												}
																											}
																											else {
																												return 0;
																											}
																										}
																										else {
																											return 1;
																										}
																									}
																									else {
																										if ( Gy <= -0.08) {
																											return 0;
																										}
																										else {
																											return 0;
																										}
																									}
																								}
																							}
																						}
																						else {
																							if ( Ay <= -0.74) {
																								if ( GxXGz <= -0.0) {
																									if ( AxXAz <= 0.02) {
																										return 1;
																									}
																									else {
																										return 0;
																									}
																								}
																								else {
																									if ( Gy <= -0.05) {
																										if ( AyXGz <= 0.07) {
																											if ( AzXGx <= 0.05) {
																												if ( Ax_squared <= -0.1) {
																													if ( Gz <= -0.07) {
																														return 0;
																													}
																													else {
																														if ( Ay <= -0.82) {
																															return 0;
																														}
																														else {
																															if ( AyXGz <= -0.02) {
																																if ( AxXAz <= 0.0) {
																																	return 0;
																																}
																																else {
																																	if ( AxXAy <= 0.2) {
																																		if ( AzXGz <= -0.06) {
																																			return 0;
																																		}
																																		else {
																																			if ( AyXAz <= 0.36) {
																																				return 0;
																																			}
																																			else {
																																				if ( GxXGz <= 0.01) {
																																					if ( AyXAz <= 0.45) {
																																						return 0;
																																					}
																																					else {
																																						return 0;
																																					}
																																				}
																																				else {
																																					return 0;
																																				}
																																			}
																																		}
																																	}
																																	else {
																																		return 0;
																																	}
																																}
																															}
																															else {
																																return 0;
																															}
																														}
																													}
																												}
																												else {
																													return 0;
																												}
																											}
																											else {
																												return 0;
																											}
																										}
																										else {
																											return 0;
																										}
																									}
																									else {
																										if ( Az <= -0.06) {
																											if ( Gy <= 0.06) {
																												if ( Gy <= 0.02) {
																													if ( AzXGx <= 0.02) {
																														return 0;
																													}
																													else {
																														return 0;
																													}
																												}
																												else {
																													return 0;
																												}
																											}
																											else {
																												if ( Az <= -0.15) {
																													if ( Az <= -0.19) {
																														return 0;
																													}
																													else {
																														return 0;
																													}
																												}
																												else {
																													if ( Gy_squared <= -0.18) {
																														return 0;
																													}
																													else {
																														return 0;
																													}
																												}
																											}
																										}
																										else {
																											if ( AxXGz <= -0.01) {
																												if ( Ax_squared <= -0.09) {
																													return 0;
																												}
																												else {
																													return 0;
																												}
																											}
																											else {
																												if ( Ay_squared <= 0.11) {
																													if ( AxXGz <= 0.01) {
																														if ( AyXGy <= -0.01) {
																															if ( AyXAz <= 0.3) {
																																return 0;
																															}
																															else {
																																if ( AxXGz <= -0.01) {
																																	if ( AxXGz <= -0.01) {
																																		return 0;
																																	}
																																	else {
																																		if ( AzXGx <= -0.03) {
																																			return 0;
																																		}
																																		else {
																																			if ( AyXGy <= -0.12) {
																																				return 0;
																																			}
																																			else {
																																				return 0;
																																			}
																																		}
																																	}
																																}
																																else {
																																	return 0;
																																}
																															}
																														}
																														else {
																															if ( Gz <= -0.11) {
																																return 0;
																															}
																															else {
																																if ( AxXGx <= -0.01) {
																																	return 0;
																																}
																																else {
																																	if ( Ay_squared <= -0.01) {
																																		return 0;
																																	}
																																	else {
																																		return 0;
																																	}
																																}
																															}
																														}
																													}
																													else {
																														return 0;
																													}
																												}
																												else {
																													return 0;
																												}
																											}
																										}
																									}
																								}
																							}
																							else {
																								if ( AyXGz <= 0.16) {
																									if ( Ay_squared <= -0.06) {
																										if ( AzXGz <= 0.03) {
																											if ( Gx_squared <= -0.16) {
																												if ( GxXGy <= 0.01) {
																													if ( AzXGx <= -0.01) {
																														return 0;
																													}
																													else {
																														if ( Az <= 0.01) {
																															if ( AxXGy <= -0.01) {
																																return 0;
																															}
																															else {
																																return 0;
																															}
																														}
																														else {
																															return 0;
																														}
																													}
																												}
																												else {
																													if ( Az_squared <= -0.11) {
																														if ( Az_squared <= -0.13) {
																															return 0;
																														}
																														else {
																															return 0;
																														}
																													}
																													else {
																														return 0;
																													}
																												}
																											}
																											else {
																												return 0;
																											}
																										}
																										else {
																											return 0;
																										}
																									}
																									else {
																										if ( AxXAy <= 0.21) {
																											if ( AyXAz <= 0.32) {
																												if ( Gx <= -0.03) {
																													return 0;
																												}
																												else {
																													if ( AzXGz <= 0.0) {
																														return 0;
																													}
																													else {
																														return 0;
																													}
																												}
																											}
																											else {
																												if ( AyXGy <= 0.01) {
																													if ( AyXAz <= 0.36) {
																														return 0;
																													}
																													else {
																														return 0;
																													}
																												}
																												else {
																													if ( AzXGx <= 0.02) {
																														if ( GyXGz <= -0.03) {
																															if ( AxXGx <= 0.01) {
																																return 0;
																															}
																															else {
																																return 0;
																															}
																														}
																														else {
																															return 0;
																														}
																													}
																													else {
																														return 0;
																													}
																												}
																											}
																										}
																										else {
																											return 0;
																										}
																									}
																								}
																								else {
																									return 1;
																								}
																							}
																						}
																					}
																				}
																				else {
																					return 1;
																				}
																			}
																		}
																	}
																	else {
																		if ( AzXGz <= 0.05) {
																			if ( AyXGz <= -0.05) {
																				return 0;
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																}
															}
															else {
																if ( AxXGz <= -0.02) {
																	if ( AyXAz <= 0.55) {
																		if ( AxXAy <= 0.22) {
																			if ( Ay <= -0.71) {
																				return 0;
																			}
																			else {
																				if ( AxXGz <= -0.03) {
																					if ( Ay <= -0.58) {
																						if ( AyXGx <= 0.01) {
																							return 1;
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						return 1;
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																		}
																		else {
																			return 0;
																		}
																	}
																	else {
																		if ( Ax <= -0.67) {
																			return 1;
																		}
																		else {
																			if ( GyXGz <= -0.02) {
																				if ( Gx_squared <= -0.16) {
																					if ( AzXGy <= -0.01) {
																						return 0;
																					}
																					else {
																						return 1;
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																}
																else {
																	if ( Gy <= -0.08) {
																		if ( AxXAy <= -0.24) {
																			return 1;
																		}
																		else {
																			if ( AzXGx <= 0.01) {
																				if ( Az_squared <= 0.02) {
																					if ( Ax <= -0.44) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					if ( Gz_squared <= -0.16) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																			else {
																				if ( Ax <= -0.04) {
																					if ( GyXGz <= -0.04) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																		}
																	}
																	else {
																		if ( AxXGy <= 0.02) {
																			if ( Az <= -0.71) {
																				if ( AxXAy <= -0.12) {
																					return 0;
																				}
																				else {
																					if ( AyXGx <= 0.02) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																			else {
																				if ( AyXAz <= 0.44) {
																					return 1;
																				}
																				else {
																					if ( AyXAz <= 0.5) {
																						if ( Ay <= -0.72) {
																							return 0;
																						}
																						else {
																							if ( AyXGy <= 0.05) {
																								if ( Ay_squared <= -0.13) {
																									return 1;
																								}
																								else {
																									return 0;
																								}
																							}
																							else {
																								return 0;
																							}
																						}
																					}
																					else {
																						if ( AxXGy <= -0.0) {
																							if ( Az_squared <= 0.05) {
																								if ( Ay_squared <= -0.12) {
																									return 0;
																								}
																								else {
																									if ( AzXGx <= -0.04) {
																										return 1;
																									}
																									else {
																										return 0;
																									}
																								}
																							}
																							else {
																								if ( AxXGy <= -0.01) {
																									return 0;
																								}
																								else {
																									return 0;
																								}
																							}
																						}
																						else {
																							if ( AxXAz <= -0.03) {
																								return 0;
																							}
																							else {
																								if ( Gx <= 0.16) {
																									if ( Ay_squared <= -0.05) {
																										return 1;
																									}
																									else {
																										return 0;
																									}
																								}
																								else {
																									return 1;
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																		else {
																			if ( GxXGy <= 0.01) {
																				if ( Gy_squared <= -0.18) {
																					return 0;
																				}
																				else {
																					return 1;
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																}
															}
														}
														else {
															if ( AyXGx <= -0.03) {
																if ( Gy_squared <= -0.18) {
																	if ( AxXGx <= -0.02) {
																		if ( AyXGz <= -0.03) {
																			return 0;
																		}
																		else {
																			return 0;
																		}
																	}
																	else {
																		if ( Gy <= -0.02) {
																			return 0;
																		}
																		else {
																			if ( AyXGy <= 0.04) {
																				if ( Az <= -1.24) {
																					if ( AxXAy <= 0.0) {
																						if ( Gy_squared <= -0.18) {
																							return 0;
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					if ( Gz <= 0.08) {
																						if ( AxXAy <= -0.07) {
																							if ( AxXAy <= -0.26) {
																								return 0;
																							}
																							else {
																								if ( Ax_squared <= -0.08) {
																									return 0;
																								}
																								else {
																									return 0;
																								}
																							}
																						}
																						else {
																							if ( Az_squared <= 0.19) {
																								return 0;
																							}
																							else {
																								if ( Gx <= 0.13) {
																									return 0;
																								}
																								else {
																									return 0;
																								}
																							}
																						}
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																}
																else {
																	if ( AyXGz <= 0.23) {
																		if ( AxXGz <= -0.03) {
																			if ( Gx <= 0.2) {
																				return 0;
																			}
																			else {
																				return 0;
																			}
																		}
																		else {
																			if ( Ax <= -0.51) {
																				if ( Gx_squared <= -0.16) {
																					return 0;
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				if ( Az <= -1.14) {
																					return 1;
																				}
																				else {
																					if ( GxXGy <= 0.01) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																		}
																	}
																	else {
																		return 1;
																	}
																}
															}
															else {
																if ( AxXGz <= -0.01) {
																	if ( Az <= -0.83) {
																		if ( AxXAy <= 0.05) {
																			if ( Gy <= 0.19) {
																				if ( AxXAy <= -0.29) {
																					return 0;
																				}
																				else {
																					if ( AxXGz <= -0.08) {
																						return 1;
																					}
																					else {
																						if ( AxXGy <= 0.0) {
																							if ( Ay_squared <= -0.2) {
																								if ( AxXAz <= -0.24) {
																									return 0;
																								}
																								else {
																									if ( Gy_squared <= -0.18) {
																										if ( Gx <= -0.01) {
																											return 1;
																										}
																										else {
																											return 1;
																										}
																									}
																									else {
																										return 0;
																									}
																								}
																							}
																							else {
																								return 0;
																							}
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																		else {
																			if ( Az <= -1.22) {
																				if ( Ax_squared <= -0.11) {
																					return 1;
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				if ( AyXGx <= -0.0) {
																					return 0;
																				}
																				else {
																					if ( Gz <= 0.1) {
																						return 1;
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																		}
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	if ( Gy <= -0.04) {
																		if ( AxXGz <= 0.0) {
																			if ( AxXGz <= -0.0) {
																				if ( AzXGx <= 0.01) {
																					return 0;
																				}
																				else {
																					if ( Ay <= -0.64) {
																						return 0;
																					}
																					else {
																						if ( AxXGz <= -0.01) {
																							return 0;
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			if ( Ay <= -0.65) {
																				return 0;
																			}
																			else {
																				if ( Ay <= -0.57) {
																					return 0;
																				}
																				else {
																					return 1;
																				}
																			}
																		}
																	}
																	else {
																		if ( Gy_squared <= -0.18) {
																			if ( AzXGz <= -0.1) {
																				return 0;
																			}
																			else {
																				if ( AzXGz <= -0.03) {
																					if ( Az <= -0.98) {
																						if ( AyXGy <= 0.04) {
																							if ( GxXGy <= 0.01) {
																								if ( AxXAy <= -0.11) {
																									return 0;
																								}
																								else {
																									if ( Gz_squared <= -0.15) {
																										return 0;
																									}
																									else {
																										return 0;
																									}
																								}
																							}
																							else {
																								return 0;
																							}
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						if ( Gz_squared <= -0.15) {
																							return 0;
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																				else {
																					if ( Gy <= 0.09) {
																						if ( Gy <= 0.01) {
																							return 0;
																						}
																						else {
																							if ( AyXGz <= 0.05) {
																								if ( AyXGz <= -0.0) {
																									return 0;
																								}
																								else {
																									return 0;
																								}
																							}
																							else {
																								return 0;
																							}
																						}
																					}
																					else {
																						if ( AxXAy <= -0.1) {
																							return 1;
																						}
																						else {
																							return 0;
																						}
																					}
																				}
																			}
																		}
																		else {
																			if ( AxXAy <= -0.08) {
																				if ( Gy <= 0.27) {
																					if ( Ay <= -0.6) {
																						return 0;
																					}
																					else {
																						return 1;
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				if ( AxXAz <= 0.02) {
																					if ( AxXAz <= -0.08) {
																						return 1;
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					if ( Gx <= -0.19) {
																						return 1;
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
													else {
														if ( Gy <= 0.11) {
															if ( Gx <= -0.05) {
																if ( Az <= 0.1) {
																	if ( GyXGz <= -0.04) {
																		return 1;
																	}
																	else {
																		if ( Ay <= -0.75) {
																			return 0;
																		}
																		else {
																			if ( Gx_squared <= -0.17) {
																				if ( AzXGy <= 0.02) {
																					if ( AxXGx <= -0.05) {
																						return 1;
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					return 1;
																				}
																			}
																			else {
																				if ( Ax <= 1.23) {
																					return 1;
																				}
																				else {
																					return 0;
																				}
																			}
																		}
																	}
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AxXAz <= -0.36) {
																	if ( Gy_squared <= -0.17) {
																		if ( Gx_squared <= -0.15) {
																			if ( GyXGz <= -0.03) {
																				if ( Az <= -0.24) {
																					if ( AyXGx <= -0.08) {
																						return 0;
																					}
																					else {
																						if ( AxXGy <= -0.03) {
																							return 0;
																						}
																						else {
																							if ( AzXGx <= -0.01) {
																								if ( Az_squared <= 0.11) {
																									return 0;
																								}
																								else {
																									return 0;
																								}
																							}
																							else {
																								return 0;
																							}
																						}
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				if ( AyXGy <= 0.1) {
																					return 0;
																				}
																				else {
																					return 0;
																				}
																			}
																		}
																		else {
																			return 0;
																		}
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	if ( AzXGx <= -0.07) {
																		return 0;
																	}
																	else {
																		if ( AyXGy <= 0.06) {
																			if ( AyXGz <= 0.11) {
																				if ( AxXAy <= -0.76) {
																					return 1;
																				}
																				else {
																					if ( Gx <= 0.09) {
																						if ( AxXAz <= -0.3) {
																							return 1;
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						if ( Gz <= -0.02) {
																							return 0;
																						}
																						else {
																							return 0;
																						}
																					}
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			if ( Az <= -0.59) {
																				return 1;
																			}
																			else {
																				if ( Gx_squared <= -0.17) {
																					return 0;
																				}
																				else {
																					if ( AzXGy <= 0.01) {
																						return 1;
																					}
																					else {
																						if ( Gy_squared <= -0.18) {
																							return 0;
																						}
																						else {
																							if ( AyXGz <= 0.07) {
																								return 1;
																							}
																							else {
																								if ( AyXGz <= 0.15) {
																									return 0;
																								}
																								else {
																									return 1;
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
														else {
															if ( AzXGz <= 0.17) {
																if ( AxXAy <= -0.59) {
																	if ( GyXGz <= -0.04) {
																		return 0;
																	}
																	else {
																		if ( Gy <= 0.29) {
																			if ( Gx_squared <= -0.17) {
																				return 0;
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																}
																else {
																	if ( Ax <= 1.12) {
																		if ( Ax <= 0.85) {
																			if ( AxXAz <= -0.24) {
																				return 0;
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			if ( AzXGy <= -0.1) {
																				return 1;
																			}
																			else {
																				if ( AxXGx <= 0.01) {
																					return 1;
																				}
																				else {
																					return 1;
																				}
																			}
																		}
																	}
																	else {
																		return 0;
																	}
																}
															}
															else {
																return 1;
															}
														}
													}
												}
											}
											else {
												if ( AxXAy <= -0.61) {
													if ( Gx <= -0.07) {
														if ( Gy_squared <= -0.18) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														if ( Gx <= 0.07) {
															return 0;
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( Az <= 2.25) {
														if ( AyXAz <= -0.65) {
															if ( Ax <= -0.28) {
																if ( Ax <= -0.37) {
																	if ( AxXGy <= 0.02) {
																		if ( Ax <= -0.55) {
																			if ( GyXGz <= -0.03) {
																				if ( AxXGy <= -0.01) {
																					return 0;
																				}
																				else {
																					if ( AxXGy <= 0.0) {
																						if ( AxXGy <= -0.01) {
																							return 1;
																						}
																						else {
																							return 1;
																						}
																					}
																					else {
																						return 1;
																					}
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																		else {
																			return 0;
																		}
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AxXAz <= 0.35) {
																	if ( AxXGz <= -0.0) {
																		return 0;
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( Gx <= -0.18) {
																if ( AyXGy <= 0.03) {
																	if ( AxXAy <= -0.46) {
																		return 0;
																	}
																	else {
																		if ( Gx_squared <= -0.16) {
																			if ( AyXGx <= 0.08) {
																				return 0;
																			}
																			else {
																				if ( Gx_squared <= -0.16) {
																					if ( Ax_squared <= -0.08) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																		}
																		else {
																			return 0;
																		}
																	}
																}
																else {
																	if ( AyXGy <= 0.03) {
																		return 0;
																	}
																	else {
																		if ( AzXGz <= 0.01) {
																			if ( Ay_squared <= -0.11) {
																				return 0;
																			}
																			else {
																				if ( AyXAz <= -0.33) {
																					if ( Gy_squared <= -0.18) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																		}
																		else {
																			return 0;
																		}
																	}
																}
															}
															else {
																if ( AzXGz <= 0.01) {
																	if ( Gy <= 0.04) {
																		if ( AxXGz <= -0.11) {
																			return 0;
																		}
																		else {
																			if ( AxXAy <= 0.5) {
																				if ( Ax_squared <= 0.0) {
																					if ( Ay <= -0.71) {
																						if ( Az_squared <= -0.06) {
																							if ( Gz_squared <= -0.15) {
																								if ( Gz <= -0.12) {
																									if ( Gz_squared <= -0.15) {
																										return 0;
																									}
																									else {
																										if ( GxXGz <= 0.01) {
																											if ( AzXGx <= 0.04) {
																												return 0;
																											}
																											else {
																												return 0;
																											}
																										}
																										else {
																											if ( Ax <= -0.2) {
																												return 0;
																											}
																											else {
																												return 0;
																											}
																										}
																									}
																								}
																								else {
																									return 0;
																								}
																							}
																							else {
																								return 0;
																							}
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																	else {
																		if ( AzXGz <= -0.05) {
																			return 0;
																		}
																		else {
																			if ( AzXGz <= -0.01) {
																				if ( AyXGy <= -0.05) {
																					if ( AxXAy <= 0.23) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					if ( Az <= 1.88) {
																						if ( Gx <= 0.05) {
																							if ( AxXAz <= -0.01) {
																								return 0;
																							}
																							else {
																								return 0;
																							}
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																			else {
																				if ( AzXGz <= -0.0) {
																					return 0;
																				}
																				else {
																					if ( Ax <= -0.04) {
																						if ( AyXGx <= -0.01) {
																							return 0;
																						}
																						else {
																							if ( AyXGz <= 0.05) {
																								return 0;
																							}
																							else {
																								return 0;
																							}
																						}
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																		}
																	}
																}
																else {
																	if ( Ax <= -1.18) {
																		if ( AyXGz <= -0.05) {
																			return 0;
																		}
																		else {
																			if ( Gz_squared <= -0.16) {
																				if ( Ax <= -1.84) {
																					return 0;
																				}
																				else {
																					if ( Ax_squared <= -0.03) {
																						if ( AzXGy <= -0.02) {
																							return 0;
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																	else {
																		if ( Gz <= 0.07) {
																			if ( AxXAz <= 0.26) {
																				if ( Gz_squared <= -0.15) {
																					if ( AxXGz <= 0.0) {
																						if ( AxXAz <= 0.19) {
																							if ( AxXGx <= -0.02) {
																								return 0;
																							}
																							else {
																								if ( Az_squared <= -0.18) {
																									if ( AyXGy <= 0.04) {
																										if ( Gx <= 0.04) {
																											if ( AxXAz <= 0.12) {
																												if ( Ax_squared <= -0.1) {
																													if ( Gx <= -0.1) {
																														return 0;
																													}
																													else {
																														if ( Az <= 1.29) {
																															return 0;
																														}
																														else {
																															return 0;
																														}
																													}
																												}
																												else {
																													return 0;
																												}
																											}
																											else {
																												return 0;
																											}
																										}
																										else {
																											return 0;
																										}
																									}
																									else {
																										if ( Az <= 1.27) {
																											return 0;
																										}
																										else {
																											return 0;
																										}
																									}
																								}
																								else {
																									if ( Gz_squared <= -0.16) {
																										if ( Gy_squared <= -0.18) {
																											if ( Ax <= -0.62) {
																												if ( Gx_squared <= -0.17) {
																													if ( Az <= 1.86) {
																														if ( AyXGz <= 0.03) {
																															if ( Az <= 1.58) {
																																return 0;
																															}
																															else {
																																return 0;
																															}
																														}
																														else {
																															return 0;
																														}
																													}
																													else {
																														return 0;
																													}
																												}
																												else {
																													return 1;
																												}
																											}
																											else {
																												if ( AyXAz <= -0.53) {
																													return 0;
																												}
																												else {
																													if ( AxXAy <= -0.24) {
																														return 0;
																													}
																													else {
																														if ( AxXAz <= 0.11) {
																															if ( AyXGy <= -0.0) {
																																return 1;
																															}
																															else {
																																if ( Ax <= -0.3) {
																																	return 0;
																																}
																																else {
																																	return 0;
																																}
																															}
																														}
																														else {
																															return 1;
																														}
																													}
																												}
																											}
																										}
																										else {
																											return 0;
																										}
																									}
																									else {
																										if ( Gz_squared <= -0.16) {
																											return 0;
																										}
																										else {
																											return 0;
																										}
																									}
																								}
																							}
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						return 1;
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																		else {
																			if ( Az <= 1.54) {
																				if ( Ax <= -0.82) {
																					return 0;
																				}
																				else {
																					if ( AxXAz <= 0.06) {
																						return 1;
																					}
																					else {
																						return 1;
																					}
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																}
															}
														}
													}
													else {
														if ( Az <= 2.75) {
															if ( Gz_squared <= -0.13) {
																if ( AyXGx <= 0.07) {
																	if ( Ay <= -0.69) {
																		return 0;
																	}
																	else {
																		if ( Az <= 2.4) {
																			if ( AxXAy <= -0.01) {
																				return 0;
																			}
																			else {
																				return 0;
																			}
																		}
																		else {
																			if ( Ax_squared <= 0.02) {
																				if ( AyXAz <= -0.78) {
																					if ( AyXGy <= 0.04) {
																						if ( Ay_squared <= -0.14) {
																							if ( AyXGx <= 0.03) {
																								return 0;
																							}
																							else {
																								return 0;
																							}
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 0;
														}
													}
												}
											}
										}
										else {
											if ( Ay <= -0.65) {
												if ( AzXGy <= -0.04) {
													if ( AyXAz <= 0.52) {
														if ( GyXGz <= -0.05) {
															return 1;
														}
														else {
															if ( GxXGy <= -0.02) {
																if ( AyXGz <= -0.05) {
																	return 0;
																}
																else {
																	if ( AyXGz <= 0.03) {
																		return 0;
																	}
																	else {
																		return 0;
																	}
																}
															}
															else {
																if ( AzXGz <= 0.02) {
																	if ( Ax <= 0.61) {
																		if ( AxXGy <= 0.01) {
																			if ( AyXAz <= -0.4) {
																				return 0;
																			}
																			else {
																				if ( GxXGz <= 0.02) {
																					return 0;
																				}
																				else {
																					return 0;
																				}
																			}
																		}
																		else {
																			return 0;
																		}
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( AxXGz <= -0.09) {
														if ( AyXGy <= 0.04) {
															if ( AxXGy <= 0.05) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															if ( GxXGz <= -0.02) {
																return 1;
															}
															else {
																if ( GxXGz <= 0.09) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( Az <= 0.12) {
															if ( Gz <= -0.12) {
																if ( GyXGz <= -0.03) {
																	if ( AyXAz <= 0.39) {
																		if ( Gz <= -0.32) {
																			return 0;
																		}
																		else {
																			return 0;
																		}
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	if ( GxXGy <= 0.05) {
																		if ( AyXGx <= -0.16) {
																			return 1;
																		}
																		else {
																			if ( AxXAy <= 0.11) {
																				if ( Ax <= -0.13) {
																					return 0;
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																	else {
																		return 1;
																	}
																}
															}
															else {
																if ( AxXAz <= -0.07) {
																	return 1;
																}
																else {
																	if ( Ax <= -0.23) {
																		if ( Gz <= 0.04) {
																			if ( Gx <= 0.26) {
																				return 0;
																			}
																			else {
																				return 0;
																			}
																		}
																		else {
																			if ( Gx <= -0.08) {
																				if ( Gx <= -0.54) {
																					return 0;
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				if ( Gx <= 0.32) {
																					if ( AxXAy <= 0.2) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					if ( AxXAy <= 0.13) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																		}
																	}
																	else {
																		if ( AxXAz <= -0.02) {
																			return 1;
																		}
																		else {
																			return 0;
																		}
																	}
																}
															}
														}
														else {
															if ( AyXAz <= 0.12) {
																if ( Gx <= -0.23) {
																	if ( AxXGy <= -0.04) {
																		return 0;
																	}
																	else {
																		if ( AyXGy <= 0.09) {
																			if ( Gx_squared <= -0.14) {
																				return 0;
																			}
																			else {
																				if ( AyXAz <= 0.07) {
																					if ( Gy_squared <= -0.18) {
																						return 1;
																					}
																					else {
																						if ( Ay_squared <= 0.13) {
																							return 0;
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																}
																else {
																	if ( GxXGy <= 0.01) {
																		if ( AzXGy <= -0.02) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		if ( GyXGz <= -0.04) {
																			return 1;
																		}
																		else {
																			return 0;
																		}
																	}
																}
															}
															else {
																if ( AxXAy <= 0.13) {
																	if ( AyXGx <= 0.37) {
																		if ( Ay <= -0.83) {
																			return 1;
																		}
																		else {
																			if ( Gx <= -0.07) {
																				if ( Gx <= -0.44) {
																					return 0;
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	if ( AyXAz <= 0.2) {
																		if ( AxXGy <= -0.02) {
																			return 1;
																		}
																		else {
																			if ( AyXGz <= 0.07) {
																				return 0;
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																	else {
																		return 0;
																	}
																}
															}
														}
													}
												}
											}
											else {
												if ( AzXGx <= -0.02) {
													if ( AxXAy <= -0.31) {
														if ( Gy <= 0.12) {
															if ( AxXGz <= -0.22) {
																return 1;
															}
															else {
																if ( Ax <= 1.05) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														if ( Az_squared <= 0.19) {
															if ( AyXAz <= 0.4) {
																return 1;
															}
															else {
																return 0;
															}
														}
														else {
															if ( AxXAz <= -0.19) {
																return 1;
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													if ( AyXGz <= 0.21) {
														if ( AyXGy <= 0.0) {
															if ( AyXAz <= 0.31) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															if ( GyXGz <= -0.03) {
																if ( AxXGx <= -0.02) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 1;
													}
												}
											}
										}
									}
									else {
										if ( Gx <= -0.21) {
											if ( Ax_squared <= -0.01) {
												if ( Ay_squared <= -0.17) {
													if ( AxXGx <= 0.03) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													if ( AyXAz <= 0.43) {
														if ( AzXGy <= -0.01) {
															if ( AxXGy <= -0.01) {
																return 1;
															}
															else {
																return 0;
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( Gx_squared <= -0.05) {
													if ( Ax_squared <= 0.29) {
														if ( AyXGx <= 0.09) {
															return 1;
														}
														else {
															if ( Az_squared <= 0.06) {
																if ( Az_squared <= -0.2) {
																	if ( Az <= 0.63) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	if ( Gy <= 0.28) {
																		if ( GyXGz <= -0.03) {
																			if ( Gy <= -0.07) {
																				return 0;
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			if ( AyXGy <= -0.06) {
																				return 0;
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																	else {
																		return 1;
																	}
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AxXGy <= -0.05) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( Ax_squared <= 0.53) {
												if ( Ax_squared <= 0.32) {
													if ( Az <= 1.73) {
														if ( Az <= 0.62) {
															if ( AxXGx <= -0.03) {
																if ( AyXGy <= 0.02) {
																	if ( Az_squared <= 0.17) {
																		if ( AyXAz <= 0.34) {
																			return 1;
																		}
																		else {
																			if ( Ay <= -0.65) {
																				return 0;
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	if ( GxXGy <= 0.01) {
																		return 0;
																	}
																	else {
																		if ( AzXGz <= -0.05) {
																			if ( AxXAy <= -0.51) {
																				return 1;
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			if ( Ax_squared <= 0.02) {
																				return 1;
																			}
																			else {
																				if ( Gz <= 0.12) {
																					return 1;
																				}
																				else {
																					return 1;
																				}
																			}
																		}
																	}
																}
															}
															else {
																if ( AxXGy <= -0.01) {
																	if ( Ay_squared <= -0.16) {
																		if ( Ax <= 1.27) {
																			if ( AyXGy <= 0.13) {
																				if ( AyXGx <= -0.07) {
																					return 0;
																				}
																				else {
																					if ( Gx_squared <= -0.17) {
																						if ( Ax_squared <= -0.04) {
																							return 0;
																						}
																						else {
																							return 1;
																						}
																					}
																					else {
																						return 1;
																					}
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			return 0;
																		}
																	}
																	else {
																		if ( Ax_squared <= 0.06) {
																			if ( Gz_squared <= -0.14) {
																				if ( AzXGz <= -0.07) {
																					return 0;
																				}
																				else {
																					if ( Gz_squared <= -0.15) {
																						return 0;
																					}
																					else {
																						if ( AzXGx <= 0.02) {
																							return 0;
																						}
																						else {
																							return 0;
																						}
																					}
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			if ( AyXGx <= -0.07) {
																				return 1;
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																}
																else {
																	if ( AxXGz <= 0.06) {
																		if ( AxXAz <= -0.27) {
																			if ( Gz <= 0.16) {
																				if ( Ax_squared <= 0.22) {
																					if ( Az_squared <= 0.21) {
																						return 0;
																					}
																					else {
																						return 1;
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			if ( AyXGz <= 0.1) {
																				if ( Gy <= 0.04) {
																					return 1;
																				}
																				else {
																					if ( AxXGy <= 0.01) {
																						return 0;
																					}
																					else {
																						if ( AxXGz <= 0.05) {
																							return 0;
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																	else {
																		if ( Az <= -0.3) {
																			if ( AxXGy <= -0.0) {
																				return 1;
																			}
																			else {
																				if ( AyXAz <= 0.45) {
																					return 0;
																				}
																				else {
																					if ( Ay <= -0.55) {
																						if ( AxXGy <= 0.02) {
																							return 0;
																						}
																						else {
																							return 1;
																						}
																					}
																					else {
																						return 1;
																					}
																				}
																			}
																		}
																		else {
																			if ( AxXAy <= -0.03) {
																				if ( Ax <= 0.86) {
																					return 1;
																				}
																				else {
																					return 1;
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																}
															}
														}
														else {
															if ( AxXAz <= 0.16) {
																if ( Gx <= 0.26) {
																	if ( GxXGy <= 0.01) {
																		if ( AyXGy <= -0.03) {
																			return 1;
																		}
																		else {
																			return 0;
																		}
																	}
																	else {
																		if ( Gx_squared <= -0.17) {
																			if ( Gz_squared <= -0.15) {
																				return 0;
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			if ( Az_squared <= -0.16) {
																				if ( AyXGy <= -0.06) {
																					return 1;
																				}
																				else {
																					return 1;
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Az <= 1.38) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( AzXGz <= 0.01) {
														if ( AyXGy <= 0.07) {
															if ( Ax_squared <= 0.42) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( AxXGx <= -0.04) {
													return 1;
												}
												else {
													if ( AxXGx <= 0.07) {
														if ( Ay_squared <= -0.38) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
											}
										}
									}
								}
								else {
									if ( GxXGz <= 0.06) {
										if ( Ax <= 0.22) {
											if ( AyXGz <= 0.17) {
												if ( Gz <= -0.15) {
													if ( AxXGz <= -0.02) {
														if ( AzXGy <= -0.22) {
															return 0;
														}
														else {
															if ( GxXGz <= -0.01) {
																return 1;
															}
															else {
																if ( Az <= -0.63) {
																	if ( Gy_squared <= -0.16) {
																		return 0;
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	if ( GxXGz <= 0.0) {
																		return 1;
																	}
																	else {
																		if ( AyXAz <= 0.38) {
																			if ( Ax_squared <= -0.1) {
																				return 1;
																			}
																			else {
																				return 0;
																			}
																		}
																		else {
																			return 0;
																		}
																	}
																}
															}
														}
													}
													else {
														if ( Gx_squared <= -0.13) {
															if ( AzXGy <= 0.09) {
																if ( AxXAy <= 0.16) {
																	if ( Ay_squared <= -0.23) {
																		return 0;
																	}
																	else {
																		if ( GxXGy <= 0.02) {
																			return 0;
																		}
																		else {
																			return 1;
																		}
																	}
																}
																else {
																	if ( AzXGy <= -0.16) {
																		if ( Gz <= -0.25) {
																			return 0;
																		}
																		else {
																			if ( AxXGz <= 0.01) {
																				return 1;
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																	else {
																		if ( AyXGx <= 0.06) {
																			return 0;
																		}
																		else {
																			return 1;
																		}
																	}
																}
															}
															else {
																if ( Gz <= -0.19) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( Ay_squared <= 0.24) {
														if ( Az <= 0.08) {
															if ( AyXGy <= 0.03) {
																if ( AzXGy <= -0.09) {
																	if ( Gz <= -0.05) {
																		if ( Az_squared <= 0.15) {
																			return 0;
																		}
																		else {
																			return 0;
																		}
																	}
																	else {
																		if ( Ay <= -0.68) {
																			if ( Az_squared <= 0.13) {
																				if ( AyXAz <= 0.6) {
																					if ( Az <= -0.36) {
																						return 0;
																					}
																					else {
																						if ( Ax_squared <= -0.09) {
																							if ( Az_squared <= -0.12) {
																								return 0;
																							}
																							else {
																								if ( Gx <= -0.08) {
																									return 0;
																								}
																								else {
																									return 0;
																								}
																							}
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																				else {
																					return 1;
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			if ( AxXAy <= -0.02) {
																				return 1;
																			}
																			else {
																				if ( AxXAy <= 0.01) {
																					return 1;
																				}
																				else {
																					if ( Gz <= 0.09) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																		}
																	}
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Ay_squared <= -0.11) {
																	if ( AzXGz <= -0.23) {
																		return 0;
																	}
																	else {
																		if ( AyXGz <= -0.13) {
																			return 0;
																		}
																		else {
																			if ( AyXGz <= 0.03) {
																				if ( Ay <= -0.64) {
																					return 0;
																				}
																				else {
																					if ( Gx <= -0.23) {
																						return 0;
																					}
																					else {
																						return 1;
																					}
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																}
																else {
																	if ( Gx <= -0.27) {
																		if ( AyXGx <= 0.33) {
																			if ( Gy_squared <= -0.15) {
																				return 0;
																			}
																			else {
																				return 0;
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		if ( Az_squared <= 0.0) {
																			if ( Gy <= -0.28) {
																				if ( Gz_squared <= -0.13) {
																					if ( AxXAy <= 0.05) {
																						if ( Az_squared <= -0.06) {
																							if ( GxXGy <= 0.01) {
																								return 0;
																							}
																							else {
																								return 0;
																							}
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						if ( Ax <= -0.82) {
																							return 0;
																						}
																						else {
																							if ( Az_squared <= -0.07) {
																								return 0;
																							}
																							else {
																								return 0;
																							}
																						}
																					}
																				}
																				else {
																					return 1;
																				}
																			}
																			else {
																				if ( Az <= -0.28) {
																					return 0;
																				}
																				else {
																					if ( AzXGz <= -0.03) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																		}
																		else {
																			if ( Az <= -0.8) {
																				return 1;
																			}
																			else {
																				if ( Az_squared <= 0.03) {
																					return 0;
																				}
																				else {
																					return 0;
																				}
																			}
																		}
																	}
																}
															}
														}
														else {
															if ( Az_squared <= -0.2) {
																if ( Ay <= -0.67) {
																	if ( Gy <= -0.41) {
																		return 0;
																	}
																	else {
																		if ( AzXGz <= -0.01) {
																			return 0;
																		}
																		else {
																			if ( Gy <= -0.03) {
																				if ( AxXAz <= 0.04) {
																					return 0;
																				}
																				else {
																					if ( Az_squared <= -0.22) {
																						return 0;
																					}
																					else {
																						if ( AzXGz <= -0.01) {
																							return 0;
																						}
																						else {
																							if ( AxXGx <= -0.0) {
																								return 1;
																							}
																							else {
																								return 1;
																							}
																						}
																					}
																				}
																			}
																			else {
																				if ( AyXGz <= -0.05) {
																					return 1;
																				}
																				else {
																					return 0;
																				}
																			}
																		}
																	}
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Ay_squared <= -0.1) {
																	if ( Az <= 1.28) {
																		return 1;
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	if ( AxXAz <= 0.07) {
																		if ( Az_squared <= -0.09) {
																			if ( Gy <= 0.37) {
																				if ( GyXGz <= -0.05) {
																					if ( Gy_squared <= -0.16) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					if ( AxXAy <= 0.18) {
																						if ( GxXGy <= 0.04) {
																							return 0;
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																			else {
																				if ( Gx <= -0.27) {
																					return 0;
																				}
																				else {
																					return 0;
																				}
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		if ( AxXGz <= -0.05) {
																			return 1;
																		}
																		else {
																			if ( GxXGz <= -0.0) {
																				return 1;
																			}
																			else {
																				if ( Gy <= 0.48) {
																					if ( AyXGy <= 0.16) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																		}
																	}
																}
															}
														}
													}
													else {
														if ( AyXGy <= 0.24) {
															return 0;
														}
														else {
															return 1;
														}
													}
												}
											}
											else {
												if ( Az_squared <= -0.1) {
													if ( AxXGz <= -0.12) {
														return 0;
													}
													else {
														if ( Gy <= 0.27) {
															if ( Az_squared <= -0.17) {
																if ( AxXAz <= 0.05) {
																	return 1;
																}
																else {
																	if ( Ax <= -0.37) {
																		return 1;
																	}
																	else {
																		return 0;
																	}
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( AyXGy <= -0.23) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( GxXGy <= -0.01) {
														return 1;
													}
													else {
														if ( AyXGy <= 0.21) {
															if ( Gz <= -0.93) {
																return 1;
															}
															else {
																if ( Gz_squared <= -0.13) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 1;
														}
													}
												}
											}
										}
										else {
											if ( Gy_squared <= -0.15) {
												if ( AzXGy <= -0.12) {
													if ( Ay_squared <= -0.44) {
														return 1;
													}
													else {
														if ( Gx_squared <= -0.16) {
															if ( Ay_squared <= -0.39) {
																return 1;
															}
															else {
																if ( Ay <= -0.55) {
																	if ( GyXGz <= -0.04) {
																		if ( AxXAy <= -0.49) {
																			return 0;
																		}
																		else {
																			if ( AzXGy <= -0.17) {
																				return 1;
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( AxXAy <= -0.45) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( AxXGy <= 0.09) {
														if ( AyXGx <= 0.09) {
															if ( AxXGz <= -0.22) {
																return 1;
															}
															else {
																if ( Ax <= 0.77) {
																	if ( Ay <= -0.71) {
																		if ( AzXGy <= -0.01) {
																			return 1;
																		}
																		else {
																			if ( AxXGy <= -0.09) {
																				return 1;
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																	else {
																		if ( Az_squared <= -0.15) {
																			return 0;
																		}
																		else {
																			if ( AyXGx <= -0.08) {
																				return 1;
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																}
																else {
																	if ( Az_squared <= 0.04) {
																		if ( AzXGz <= -0.03) {
																			return 0;
																		}
																		else {
																			if ( Ax_squared <= 0.46) {
																				if ( AxXGz <= -0.13) {
																					return 1;
																				}
																				else {
																					if ( AyXAz <= 0.28) {
																						if ( Gx_squared <= -0.15) {
																							return 1;
																						}
																						else {
																							return 1;
																						}
																					}
																					else {
																						return 1;
																					}
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																	else {
																		return 0;
																	}
																}
															}
														}
														else {
															if ( Gz <= -0.12) {
																return 0;
															}
															else {
																if ( Gy_squared <= -0.16) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( AxXAz <= -0.01) {
															if ( AyXGz <= 0.04) {
																if ( Az <= 0.23) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Ay <= -0.7) {
																	return 1;
																}
																else {
																	if ( AxXGy <= 0.14) {
																		return 0;
																	}
																	else {
																		return 0;
																	}
																}
															}
														}
														else {
															if ( Az_squared <= 0.41) {
																if ( Gz <= 0.1) {
																	if ( AxXGy <= 0.18) {
																		if ( AzXGy <= -0.03) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
											}
											else {
												if ( AyXGy <= -0.04) {
													if ( AxXAz <= -0.15) {
														if ( AyXGz <= -0.02) {
															if ( Ay <= -0.7) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															if ( AzXGx <= -0.06) {
																return 0;
															}
															else {
																if ( Az_squared <= 0.21) {
																	if ( Az <= -0.54) {
																		return 0;
																	}
																	else {
																		if ( AzXGz <= 0.01) {
																			return 1;
																		}
																		else {
																			if ( AxXGx <= 0.07) {
																				return 0;
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( Ax <= 0.89) {
															if ( AzXGx <= 0.06) {
																if ( AyXGy <= -0.29) {
																	return 1;
																}
																else {
																	if ( Az <= 0.44) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( Gz_squared <= -0.14) {
																if ( Gz <= 0.15) {
																	if ( GxXGy <= -0.02) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( AxXGx <= 0.1) {
														if ( Ax_squared <= 0.07) {
															if ( Az_squared <= 0.03) {
																if ( Gy_squared <= -0.14) {
																	if ( Gy_squared <= -0.14) {
																		if ( Gz <= -0.05) {
																			return 0;
																		}
																		else {
																			return 0;
																		}
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( Ay <= -0.68) {
																if ( AyXGz <= -0.16) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AyXAz <= -0.06) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
											}
										}
									}
									else {
										if ( GxXGy <= -0.09) {
											return 1;
										}
										else {
											if ( AxXGy <= 0.05) {
												if ( Az_squared <= -0.14) {
													if ( AxXGy <= -0.05) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													if ( Gz_squared <= 0.12) {
														return 1;
													}
													else {
														return 1;
													}
												}
											}
											else {
												return 1;
											}
										}
									}
								}
							}
						}
						else {
							if ( AyXGz <= -0.13) {
								if ( Gx <= -0.15) {
									if ( Gz_squared <= 0.28) {
										if ( Gz <= -1.43) {
											if ( Gz <= -1.6) {
												return 1;
											}
											else {
												return 1;
											}
										}
										else {
											if ( Az <= 1.32) {
												if ( AxXGx <= -0.06) {
													if ( GyXGz <= -0.09) {
														return 1;
													}
													else {
														if ( AyXGz <= -0.26) {
															if ( Ay <= 1.35) {
																if ( AxXGx <= -0.25) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( AyXGy <= -0.16) {
																return 1;
															}
															else {
																if ( Az_squared <= 0.07) {
																	if ( GyXGz <= -0.05) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( AyXAz <= -0.48) {
														if ( Az <= -0.8) {
															return 1;
														}
														else {
															if ( Az_squared <= -0.07) {
																return 0;
															}
															else {
																if ( Az <= -0.29) {
																	if ( Gy_squared <= -0.16) {
																		if ( Gy_squared <= -0.18) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( AyXGz <= -0.42) {
															return 0;
														}
														else {
															if ( AzXGx <= 0.1) {
																if ( GxXGy <= 0.03) {
																	if ( Gy_squared <= -0.18) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( Gx_squared <= -0.11) {
											return 1;
										}
										else {
											return 1;
										}
									}
								}
								else {
									if ( Ax_squared <= -0.08) {
										if ( AxXGz <= -0.04) {
											if ( Ax <= -0.03) {
												if ( AyXGx <= -0.03) {
													return 0;
												}
												else {
													if ( AzXGy <= 0.11) {
														if ( Ax <= -0.08) {
															if ( Gx <= -0.01) {
																return 1;
															}
															else {
																if ( Gy <= -0.11) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( Gy_squared <= -0.17) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( Az <= 0.82) {
												if ( Az_squared <= 0.11) {
													if ( Gy_squared <= -0.17) {
														if ( AyXGx <= -0.01) {
															return 0;
														}
														else {
															if ( Ay <= 1.38) {
																if ( Az <= -0.14) {
																	if ( AzXGx <= -0.09) {
																		return 1;
																	}
																	else {
																		if ( AzXGx <= 0.0) {
																			return 0;
																		}
																		else {
																			return 0;
																		}
																	}
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( Az_squared <= -0.09) {
															return 1;
														}
														else {
															if ( Az_squared <= 0.03) {
																if ( AxXGz <= -0.01) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
									}
									else {
										if ( Gy_squared <= -0.16) {
											if ( Az_squared <= 0.07) {
												if ( AyXGx <= 0.08) {
													if ( Gx_squared <= -0.17) {
														if ( GyXGz <= -0.08) {
															return 1;
														}
														else {
															if ( Gy <= -0.13) {
																return 1;
															}
															else {
																if ( GxXGy <= 0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( Gy_squared <= -0.17) {
														return 1;
													}
													else {
														return 1;
													}
												}
											}
											else {
												return 1;
											}
										}
										else {
											if ( Ay_squared <= 0.26) {
												if ( AzXGy <= -0.07) {
													return 1;
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
									}
								}
							}
							else {
								if ( Az <= 1.43) {
									if ( Ax <= 2.69) {
										if ( Gx <= -0.66) {
											if ( AxXGx <= 0.08) {
												if ( AzXGx <= 0.25) {
													if ( Ax <= -0.07) {
														if ( GxXGy <= -0.04) {
															return 1;
														}
														else {
															if ( AyXGx <= -0.27) {
																if ( GyXGz <= -0.05) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( Az <= 0.83) {
															if ( AzXGy <= -0.0) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( GxXGy <= 0.13) {
														if ( Az <= -0.66) {
															if ( AxXGy <= -0.03) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															if ( Az <= -0.31) {
																if ( AxXGx <= -0.27) {
																	return 1;
																}
																else {
																	if ( Ax <= 0.24) {
																		if ( Az_squared <= -0.01) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		return 0;
																	}
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												return 1;
											}
										}
										else {
											if ( AzXGx <= 0.06) {
												if ( AxXAz <= 0.0) {
													if ( Ax_squared <= 0.48) {
														if ( Az_squared <= 0.42) {
															if ( Az_squared <= -0.08) {
																if ( AxXAz <= -0.17) {
																	return 1;
																}
																else {
																	if ( AzXGx <= 0.02) {
																		if ( AxXGy <= -0.09) {
																			return 0;
																		}
																		else {
																			if ( Gz <= 0.16) {
																				if ( Gz <= 0.04) {
																					if ( Gy <= -0.14) {
																						if ( AxXAz <= -0.07) {
																							return 1;
																						}
																						else {
																							if ( Ax <= 0.25) {
																								return 1;
																							}
																							else {
																								return 1;
																							}
																						}
																					}
																					else {
																						if ( Gy <= 0.45) {
																							if ( Az <= 0.07) {
																								if ( Ax <= 0.49) {
																									if ( Gx_squared <= -0.16) {
																										if ( AxXGx <= 0.0) {
																											return 1;
																										}
																										else {
																											if ( AxXAz <= -0.04) {
																												return 1;
																											}
																											else {
																												return 1;
																											}
																										}
																									}
																									else {
																										return 1;
																									}
																								}
																								else {
																									return 0;
																								}
																							}
																							else {
																								if ( Gy <= 0.34) {
																									if ( Gy_squared <= -0.17) {
																										if ( AzXGx <= -0.0) {
																											return 1;
																										}
																										else {
																											return 1;
																										}
																									}
																									else {
																										return 1;
																									}
																								}
																								else {
																									return 1;
																								}
																							}
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																				else {
																					if ( Gx <= 0.24) {
																						if ( Az <= 0.18) {
																							if ( Gz_squared <= -0.15) {
																								return 1;
																							}
																							else {
																								if ( Az <= -0.1) {
																									return 1;
																								}
																								else {
																									if ( AxXAy <= 0.48) {
																										if ( GxXGz <= 0.01) {
																											return 1;
																										}
																										else {
																											return 0;
																										}
																									}
																									else {
																										return 0;
																									}
																								}
																							}
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						return 1;
																					}
																				}
																			}
																			else {
																				if ( AyXGy <= 0.24) {
																					if ( AyXGy <= 0.12) {
																						if ( AyXGy <= -0.12) {
																							return 0;
																						}
																						else {
																							if ( GxXGy <= 0.01) {
																								if ( AxXAz <= -0.12) {
																									return 1;
																								}
																								else {
																									if ( AyXGy <= -0.1) {
																										return 0;
																									}
																									else {
																										if ( AxXAz <= -0.02) {
																											if ( Gx <= 0.2) {
																												if ( AyXAz <= -0.48) {
																													return 1;
																												}
																												else {
																													return 0;
																												}
																											}
																											else {
																												return 1;
																											}
																										}
																										else {
																											if ( AyXAz <= -0.37) {
																												return 1;
																											}
																											else {
																												return 1;
																											}
																										}
																									}
																								}
																							}
																							else {
																								return 1;
																							}
																						}
																					}
																					else {
																						return 1;
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																		}
																	}
																	else {
																		if ( Az <= -0.17) {
																			if ( AzXGy <= -0.03) {
																				return 1;
																			}
																			else {
																				if ( AxXGy <= -0.04) {
																					return 1;
																				}
																				else {
																					return 0;
																				}
																			}
																		}
																		else {
																			if ( Gy_squared <= -0.18) {
																				if ( AzXGy <= -0.04) {
																					return 1;
																				}
																				else {
																					if ( Az_squared <= -0.17) {
																						if ( Az_squared <= -0.2) {
																							return 1;
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						if ( Az_squared <= -0.12) {
																							if ( Ay <= 1.36) {
																								if ( AyXGz <= -0.02) {
																									return 0;
																								}
																								else {
																									if ( Ay <= 1.33) {
																										if ( AyXAz <= -0.39) {
																											if ( Gz <= 0.03) {
																												return 1;
																											}
																											else {
																												return 1;
																											}
																										}
																										else {
																											return 0;
																										}
																									}
																									else {
																										return 1;
																									}
																								}
																							}
																							else {
																								return 1;
																							}
																						}
																						else {
																							return 0;
																						}
																					}
																				}
																			}
																			else {
																				if ( AzXGx <= 0.03) {
																					if ( Az <= 0.21) {
																						if ( Gy <= -0.13) {
																							return 1;
																						}
																						else {
																							return 1;
																						}
																					}
																					else {
																						return 1;
																					}
																				}
																				else {
																					if ( Az_squared <= -0.17) {
																						if ( GxXGz <= 0.0) {
																							if ( AzXGx <= 0.05) {
																								if ( AyXAz <= -0.26) {
																									return 0;
																								}
																								else {
																									return 0;
																								}
																							}
																							else {
																								return 1;
																							}
																						}
																						else {
																							return 1;
																						}
																					}
																					else {
																						if ( Ay_squared <= 0.04) {
																							if ( Gx <= -0.24) {
																								return 1;
																							}
																							else {
																								if ( Gx_squared <= -0.17) {
																									return 1;
																								}
																								else {
																									if ( AxXGy <= -0.07) {
																										return 1;
																									}
																									else {
																										if ( Az <= 0.13) {
																											if ( AzXGx <= 0.06) {
																												if ( Gy_squared <= -0.16) {
																													if ( AzXGz <= -0.01) {
																														if ( AxXGz <= 0.03) {
																															return 1;
																														}
																														else {
																															return 1;
																														}
																													}
																													else {
																														return 1;
																													}
																												}
																												else {
																													return 0;
																												}
																											}
																											else {
																												return 0;
																											}
																										}
																										else {
																											return 0;
																										}
																									}
																								}
																							}
																						}
																						else {
																							return 0;
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
															else {
																if ( AyXAz <= 0.37) {
																	if ( Az <= -1.04) {
																		return 1;
																	}
																	else {
																		if ( Az_squared <= 0.13) {
																			if ( Gy_squared <= -0.17) {
																				if ( AxXGy <= -0.01) {
																					if ( GyXGz <= -0.06) {
																						return 1;
																					}
																					else {
																						if ( AzXGx <= -0.02) {
																							if ( AzXGz <= -0.02) {
																								if ( AyXGz <= 0.17) {
																									return 1;
																								}
																								else {
																									return 1;
																								}
																							}
																							else {
																								return 1;
																							}
																						}
																						else {
																							if ( AzXGz <= -0.1) {
																								return 1;
																							}
																							else {
																								if ( Gy_squared <= -0.18) {
																									if ( AxXGy <= -0.03) {
																										return 1;
																									}
																									else {
																										if ( Gy <= -0.06) {
																											return 1;
																										}
																										else {
																											if ( AxXAy <= 0.45) {
																												return 1;
																											}
																											else {
																												return 1;
																											}
																										}
																									}
																								}
																								else {
																									return 1;
																								}
																							}
																						}
																					}
																				}
																				else {
																					if ( AxXGx <= 0.04) {
																						if ( AyXGx <= 0.08) {
																							if ( Gz <= 0.16) {
																								if ( Gy_squared <= -0.17) {
																									if ( AzXGy <= -0.02) {
																										if ( Gx <= 0.05) {
																											if ( Gy <= 0.08) {
																												return 1;
																											}
																											else {
																												if ( Ax <= 0.09) {
																													return 1;
																												}
																												else {
																													if ( Az <= -0.47) {
																														return 1;
																													}
																													else {
																														return 1;
																													}
																												}
																											}
																										}
																										else {
																											return 1;
																										}
																									}
																									else {
																										return 1;
																									}
																								}
																								else {
																									return 1;
																								}
																							}
																							else {
																								if ( AyXGx <= -0.03) {
																									return 1;
																								}
																								else {
																									return 1;
																								}
																							}
																						}
																						else {
																							return 1;
																						}
																					}
																					else {
																						if ( AzXGz <= 0.0) {
																							if ( AyXAz <= -0.61) {
																								return 1;
																							}
																							else {
																								return 1;
																							}
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																			}
																			else {
																				if ( GyXGz <= -0.03) {
																					if ( Gz <= 0.65) {
																						if ( AxXGz <= -0.0) {
																							if ( Az <= -0.44) {
																								if ( Gz <= -0.15) {
																									return 1;
																								}
																								else {
																									return 1;
																								}
																							}
																							else {
																								if ( AzXGz <= 0.01) {
																									return 1;
																								}
																								else {
																									return 1;
																								}
																							}
																						}
																						else {
																							if ( GxXGz <= 0.0) {
																								return 1;
																							}
																							else {
																								if ( Az <= -0.54) {
																									return 1;
																								}
																								else {
																									if ( AzXGy <= 0.13) {
																										if ( Gz <= 0.08) {
																											return 1;
																										}
																										else {
																											if ( AzXGz <= -0.09) {
																												return 1;
																											}
																											else {
																												return 1;
																											}
																										}
																									}
																									else {
																										return 1;
																									}
																								}
																							}
																						}
																					}
																					else {
																						return 1;
																					}
																				}
																				else {
																					if ( GxXGy <= -0.01) {
																						return 1;
																					}
																					else {
																						if ( AyXGx <= 0.09) {
																							if ( AxXAy <= 0.5) {
																								if ( AxXGy <= 0.04) {
																									return 1;
																								}
																								else {
																									return 1;
																								}
																							}
																							else {
																								return 1;
																							}
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																			}
																		}
																		else {
																			if ( AzXGx <= 0.04) {
																				if ( AzXGx <= -0.07) {
																					return 1;
																				}
																				else {
																					return 1;
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																}
																else {
																	if ( AyXGz <= -0.01) {
																		return 0;
																	}
																	else {
																		return 1;
																	}
																}
															}
														}
														else {
															if ( AxXAz <= -0.6) {
																if ( AyXAz <= -0.6) {
																	return 0;
																}
																else {
																	if ( Gy <= -0.07) {
																		return 0;
																	}
																	else {
																		if ( Gz_squared <= -0.15) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																}
															}
															else {
																if ( AzXGy <= 0.05) {
																	if ( Ay <= -0.17) {
																		if ( Ax_squared <= -0.02) {
																			if ( Gz_squared <= -0.15) {
																				if ( GxXGz <= 0.0) {
																					return 0;
																				}
																				else {
																					if ( AyXGx <= -0.01) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	if ( Ay <= -0.21) {
																		return 0;
																	}
																	else {
																		return 1;
																	}
																}
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( AxXAy <= 0.82) {
														if ( Az <= -1.49) {
															if ( Gy <= 0.13) {
																if ( Gy <= -0.22) {
																	return 1;
																}
																else {
																	if ( AyXGy <= 0.01) {
																		return 0;
																	}
																	else {
																		return 0;
																	}
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( Gz_squared <= -0.05) {
																if ( AyXGz <= 0.04) {
																	if ( Gy <= -0.06) {
																		if ( AxXGy <= -0.02) {
																			if ( AxXGz <= -0.04) {
																				return 1;
																			}
																			else {
																				if ( Ax_squared <= -0.03) {
																					if ( AyXGz <= 0.03) {
																						if ( Gx_squared <= -0.15) {
																							if ( Az <= 0.98) {
																								if ( Gy_squared <= -0.15) {
																									if ( AxXAz <= 0.04) {
																										return 0;
																									}
																									else {
																										return 0;
																									}
																								}
																								else {
																									return 1;
																								}
																							}
																							else {
																								return 1;
																							}
																						}
																						else {
																							return 1;
																						}
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					return 1;
																				}
																			}
																		}
																		else {
																			if ( AyXAz <= -0.6) {
																				if ( Gy_squared <= -0.18) {
																					return 0;
																				}
																				else {
																					if ( AzXGx <= 0.02) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																			else {
																				if ( AzXGy <= -0.03) {
																					return 1;
																				}
																				else {
																					if ( AyXAz <= -0.31) {
																						if ( Gy_squared <= -0.16) {
																							if ( AyXAz <= -0.51) {
																								return 0;
																							}
																							else {
																								if ( Gx <= -0.04) {
																									if ( AzXGz <= 0.01) {
																										return 0;
																									}
																									else {
																										if ( GxXGy <= 0.02) {
																											return 0;
																										}
																										else {
																											return 1;
																										}
																									}
																								}
																								else {
																									if ( AyXGx <= 0.03) {
																										return 0;
																									}
																									else {
																										if ( AyXAz <= -0.4) {
																											return 1;
																										}
																										else {
																											return 0;
																										}
																									}
																								}
																							}
																						}
																						else {
																							return 1;
																						}
																					}
																					else {
																						if ( AxXGy <= -0.01) {
																							if ( AyXAz <= -0.21) {
																								return 0;
																							}
																							else {
																								return 1;
																							}
																						}
																						else {
																							if ( Gy <= -0.11) {
																								if ( AxXGx <= -0.03) {
																									return 0;
																								}
																								else {
																									if ( AyXAz <= -0.08) {
																										if ( GxXGy <= 0.0) {
																											return 0;
																										}
																										else {
																											if ( AzXGz <= 0.01) {
																												return 0;
																											}
																											else {
																												return 0;
																											}
																										}
																									}
																									else {
																										return 1;
																									}
																								}
																							}
																							else {
																								return 0;
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																	else {
																		if ( AxXAy <= 0.3) {
																			if ( Gy <= 0.08) {
																				if ( AxXAy <= 0.13) {
																					if ( Ay <= 1.3) {
																						if ( AyXAz <= -0.16) {
																							if ( Az_squared <= -0.07) {
																								if ( AyXAz <= -0.3) {
																									return 0;
																								}
																								else {
																									return 0;
																								}
																							}
																							else {
																								if ( Ay <= 1.26) {
																									return 0;
																								}
																								else {
																									if ( AzXGz <= 0.06) {
																										if ( AyXAz <= -0.63) {
																											return 0;
																										}
																										else {
																											if ( Ay_squared <= -0.09) {
																												return 0;
																											}
																											else {
																												if ( Az_squared <= -0.03) {
																													if ( Az <= -0.3) {
																														if ( Ay_squared <= -0.05) {
																															return 0;
																														}
																														else {
																															return 0;
																														}
																													}
																													else {
																														return 0;
																													}
																												}
																												else {
																													return 0;
																												}
																											}
																										}
																									}
																									else {
																										return 0;
																									}
																								}
																							}
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						if ( Gx_squared <= -0.16) {
																							if ( Gx_squared <= -0.17) {
																								return 0;
																							}
																							else {
																								if ( Gz <= -0.16) {
																									return 0;
																								}
																								else {
																									return 0;
																								}
																							}
																						}
																						else {
																							return 0;
																						}
																					}
																				}
																				else {
																					if ( AyXGz <= -0.02) {
																						if ( Ax_squared <= -0.11) {
																							if ( Az <= -0.24) {
																								return 0;
																							}
																							else {
																								return 0;
																							}
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						if ( AxXAz <= 0.03) {
																							return 1;
																						}
																						else {
																							if ( Ax <= -0.38) {
																								return 0;
																							}
																							else {
																								return 0;
																							}
																						}
																					}
																				}
																			}
																			else {
																				if ( AyXGy <= 0.17) {
																					if ( AxXAz <= 0.06) {
																						if ( Az <= -0.32) {
																							return 0;
																						}
																						else {
																							if ( Az <= 0.7) {
																								if ( Az_squared <= -0.17) {
																									return 0;
																								}
																								else {
																									if ( Ax <= -0.25) {
																										return 1;
																									}
																									else {
																										return 1;
																									}
																								}
																							}
																							else {
																								return 1;
																							}
																						}
																					}
																					else {
																						if ( Gy_squared <= -0.18) {
																							if ( Gy <= 0.1) {
																								return 0;
																							}
																							else {
																								if ( Gy_squared <= -0.18) {
																									return 0;
																								}
																								else {
																									if ( Ay_squared <= -0.11) {
																										return 0;
																									}
																									else {
																										return 0;
																									}
																								}
																							}
																						}
																						else {
																							if ( AzXGx <= -0.01) {
																								return 0;
																							}
																							else {
																								if ( AyXGz <= 0.01) {
																									return 0;
																								}
																								else {
																									return 0;
																								}
																							}
																						}
																					}
																				}
																				else {
																					if ( AyXGy <= 0.24) {
																						if ( Az_squared <= -0.21) {
																							return 1;
																						}
																						else {
																							return 1;
																						}
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																		}
																		else {
																			if ( Ax <= 0.47) {
																				if ( Ay_squared <= 0.12) {
																					if ( Gx <= -0.26) {
																						return 1;
																					}
																					else {
																						if ( GxXGz <= 0.0) {
																							return 1;
																						}
																						else {
																							if ( AxXGy <= 0.03) {
																								if ( Gx_squared <= -0.17) {
																									return 1;
																								}
																								else {
																									return 1;
																								}
																							}
																							else {
																								return 0;
																							}
																						}
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																}
																else {
																	if ( Gz <= 0.41) {
																		if ( AzXGz <= -0.1) {
																			if ( Gy <= -0.19) {
																				return 1;
																			}
																			else {
																				if ( Gy <= 0.09) {
																					return 1;
																				}
																				else {
																					return 0;
																				}
																			}
																		}
																		else {
																			if ( AxXAy <= 0.42) {
																				if ( GxXGy <= 0.02) {
																					if ( Ax <= -0.3) {
																						if ( Az <= 1.09) {
																							if ( Az_squared <= 0.05) {
																								if ( Az <= 0.3) {
																									if ( Az <= -0.17) {
																										if ( Gy_squared <= -0.18) {
																											if ( Az_squared <= -0.08) {
																												return 1;
																											}
																											else {
																												if ( Az <= -0.29) {
																													if ( AzXGz <= -0.02) {
																														return 0;
																													}
																													else {
																														return 0;
																													}
																												}
																												else {
																													return 0;
																												}
																											}
																										}
																										else {
																											if ( AzXGy <= 0.12) {
																												if ( AxXAz <= 0.06) {
																													return 1;
																												}
																												else {
																													if ( Az <= -0.28) {
																														return 0;
																													}
																													else {
																														return 0;
																													}
																												}
																											}
																											else {
																												return 1;
																											}
																										}
																									}
																									else {
																										if ( Az_squared <= -0.16) {
																											if ( Ax <= -0.5) {
																												if ( Az <= 0.2) {
																													if ( AzXGy <= -0.03) {
																														return 0;
																													}
																													else {
																														if ( Az_squared <= -0.17) {
																															if ( Gx <= -0.05) {
																																return 0;
																															}
																															else {
																																return 0;
																															}
																														}
																														else {
																															if ( AyXGz <= 0.07) {
																																return 0;
																															}
																															else {
																																if ( Gz <= 0.14) {
																																	return 1;
																																}
																																else {
																																	return 1;
																																}
																															}
																														}
																													}
																												}
																												else {
																													if ( AyXGx <= -0.07) {
																														return 0;
																													}
																													else {
																														if ( AyXGy <= -0.06) {
																															if ( AzXGz <= -0.02) {
																																return 0;
																															}
																															else {
																																return 0;
																															}
																														}
																														else {
																															return 0;
																														}
																													}
																												}
																											}
																											else {
																												if ( Ax_squared <= -0.11) {
																													if ( AzXGy <= 0.0) {
																														if ( AxXGx <= -0.0) {
																															return 1;
																														}
																														else {
																															return 0;
																														}
																													}
																													else {
																														if ( Ax_squared <= -0.12) {
																															return 0;
																														}
																														else {
																															return 1;
																														}
																													}
																												}
																												else {
																													return 1;
																												}
																											}
																										}
																										else {
																											if ( AzXGy <= -0.02) {
																												if ( AyXGy <= 0.1) {
																													if ( Az_squared <= -0.13) {
																														return 1;
																													}
																													else {
																														return 1;
																													}
																												}
																												else {
																													return 1;
																												}
																											}
																											else {
																												if ( AzXGy <= 0.01) {
																													if ( Gz_squared <= -0.15) {
																														return 1;
																													}
																													else {
																														if ( AxXGy <= -0.0) {
																															return 1;
																														}
																														else {
																															if ( Gy <= 0.01) {
																																return 0;
																															}
																															else {
																																return 1;
																															}
																														}
																													}
																												}
																												else {
																													if ( AyXGz <= 0.19) {
																														if ( Ax <= -0.43) {
																															if ( Gz_squared <= -0.15) {
																																return 0;
																															}
																															else {
																																if ( Az <= 0.03) {
																																	if ( GxXGz <= 0.01) {
																																		return 1;
																																	}
																																	else {
																																		return 0;
																																	}
																																}
																																else {
																																	return 0;
																																}
																															}
																														}
																														else {
																															if ( Ay_squared <= -0.03) {
																																return 1;
																															}
																															else {
																																return 1;
																															}
																														}
																													}
																													else {
																														return 1;
																													}
																												}
																											}
																										}
																									}
																								}
																								else {
																									if ( Az_squared <= -0.2) {
																										if ( Ax <= -0.49) {
																											if ( AyXAz <= 0.01) {
																												if ( Gy_squared <= -0.18) {
																													if ( Az <= 0.76) {
																														if ( AxXAy <= 0.01) {
																															if ( Gz <= 0.24) {
																																if ( AyXGz <= 0.11) {
																																	return 0;
																																}
																																else {
																																	return 0;
																																}
																															}
																															else {
																																return 0;
																															}
																														}
																														else {
																															if ( AxXAz <= 0.06) {
																																return 0;
																															}
																															else {
																																return 0;
																															}
																														}
																													}
																													else {
																														return 1;
																													}
																												}
																												else {
																													if ( GxXGy <= 0.01) {
																														if ( AyXAz <= -0.2) {
																															return 0;
																														}
																														else {
																															if ( AxXGy <= 0.02) {
																																if ( AxXGy <= -0.01) {
																																	return 1;
																																}
																																else {
																																	if ( Gy_squared <= -0.17) {
																																		return 0;
																																	}
																																	else {
																																		return 1;
																																	}
																																}
																															}
																															else {
																																if ( AzXGz <= -0.0) {
																																	return 0;
																																}
																																else {
																																	if ( Gy_squared <= -0.17) {
																																		return 0;
																																	}
																																	else {
																																		return 1;
																																	}
																																}
																															}
																														}
																													}
																													else {
																														if ( Ax <= -1.09) {
																															return 0;
																														}
																														else {
																															if ( AxXAz <= 0.07) {
																																return 0;
																															}
																															else {
																																return 1;
																															}
																														}
																													}
																												}
																											}
																											else {
																												return 1;
																											}
																										}
																										else {
																											if ( Az_squared <= -0.22) {
																												return 0;
																											}
																											else {
																												if ( Az_squared <= -0.21) {
																													return 0;
																												}
																												else {
																													return 0;
																												}
																											}
																										}
																									}
																									else {
																										if ( Ax <= -1.01) {
																											return 0;
																										}
																										else {
																											if ( GxXGy <= 0.01) {
																												if ( Gz_squared <= -0.14) {
																													if ( AzXGy <= 0.03) {
																														if ( AzXGz <= 0.0) {
																															if ( Gz <= 0.2) {
																																if ( AxXAy <= 0.03) {
																																	return 0;
																																}
																																else {
																																	return 0;
																																}
																															}
																															else {
																																return 0;
																															}
																														}
																														else {
																															return 0;
																														}
																													}
																													else {
																														return 0;
																													}
																												}
																												else {
																													return 0;
																												}
																											}
																											else {
																												if ( GyXGz <= -0.04) {
																													return 0;
																												}
																												else {
																													if ( GyXGz <= -0.03) {
																														if ( AzXGy <= 0.01) {
																															if ( AyXAz <= -0.3) {
																																return 1;
																															}
																															else {
																																if ( AzXGz <= 0.01) {
																																	return 0;
																																}
																																else {
																																	return 1;
																																}
																															}
																														}
																														else {
																															return 0;
																														}
																													}
																													else {
																														return 0;
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																							else {
																								return 1;
																							}
																						}
																						else {
																							return 1;
																						}
																					}
																					else {
																						if ( Az_squared <= -0.16) {
																							if ( Az_squared <= -0.16) {
																								if ( Az_squared <= -0.19) {
																									if ( AyXAz <= -0.19) {
																										if ( Gy <= 0.32) {
																											if ( AyXGx <= 0.0) {
																												if ( AxXGy <= 0.0) {
																													if ( AxXAy <= 0.23) {
																														return 0;
																													}
																													else {
																														if ( Az_squared <= -0.2) {
																															return 0;
																														}
																														else {
																															return 0;
																														}
																													}
																												}
																												else {
																													return 0;
																												}
																											}
																											else {
																												if ( Gy <= 0.01) {
																													if ( AyXGx <= 0.08) {
																														return 0;
																													}
																													else {
																														return 0;
																													}
																												}
																												else {
																													return 0;
																												}
																											}
																										}
																										else {
																											return 0;
																										}
																									}
																									else {
																										if ( AxXAz <= 0.06) {
																											if ( Gz <= 0.22) {
																												if ( AyXAz <= -0.1) {
																													if ( AxXGy <= -0.03) {
																														return 1;
																													}
																													else {
																														return 0;
																													}
																												}
																												else {
																													return 0;
																												}
																											}
																											else {
																												return 0;
																											}
																										}
																										else {
																											if ( Az_squared <= -0.21) {
																												if ( Az_squared <= -0.21) {
																													if ( AxXGx <= 0.01) {
																														return 1;
																													}
																													else {
																														return 1;
																													}
																												}
																												else {
																													return 1;
																												}
																											}
																											else {
																												return 0;
																											}
																										}
																									}
																								}
																								else {
																									if ( Az_squared <= -0.18) {
																										if ( Az_squared <= -0.18) {
																											return 0;
																										}
																										else {
																											return 1;
																										}
																									}
																									else {
																										if ( AyXGz <= 0.15) {
																											if ( AzXGx <= 0.01) {
																												return 1;
																											}
																											else {
																												return 1;
																											}
																										}
																										else {
																											return 0;
																										}
																									}
																								}
																							}
																							else {
																								return 1;
																							}
																						}
																						else {
																							if ( AxXGz <= 0.0) {
																								if ( Az_squared <= -0.13) {
																									if ( AyXAz <= -0.45) {
																										return 1;
																									}
																									else {
																										if ( GyXGz <= -0.04) {
																											return 1;
																										}
																										else {
																											if ( GyXGz <= -0.04) {
																												return 1;
																											}
																											else {
																												if ( AxXGy <= -0.02) {
																													return 0;
																												}
																												else {
																													return 1;
																												}
																											}
																										}
																									}
																								}
																								else {
																									if ( Ay_squared <= -0.05) {
																										return 1;
																									}
																									else {
																										return 0;
																									}
																								}
																							}
																							else {
																								if ( Gx <= 0.0) {
																									return 0;
																								}
																								else {
																									if ( AzXGy <= -0.0) {
																										return 1;
																									}
																									else {
																										return 1;
																									}
																								}
																							}
																						}
																					}
																				}
																				else {
																					if ( AzXGz <= 0.01) {
																						if ( Gy_squared <= -0.16) {
																							if ( GyXGz <= -0.02) {
																								if ( Gy <= 0.16) {
																									if ( AxXGy <= 0.03) {
																										if ( AyXAz <= -0.23) {
																											if ( AxXGy <= 0.0) {
																												if ( GxXGz <= -0.01) {
																													return 0;
																												}
																												else {
																													return 0;
																												}
																											}
																											else {
																												return 1;
																											}
																										}
																										else {
																											return 0;
																										}
																									}
																									else {
																										return 0;
																									}
																								}
																								else {
																									if ( AyXGz <= 0.07) {
																										return 1;
																									}
																									else {
																										if ( AzXGy <= -0.03) {
																											if ( Ax <= -0.85) {
																												return 0;
																											}
																											else {
																												if ( Az_squared <= -0.15) {
																													if ( Az_squared <= -0.2) {
																														return 0;
																													}
																													else {
																														return 0;
																													}
																												}
																												else {
																													return 0;
																												}
																											}
																										}
																										else {
																											return 0;
																										}
																									}
																								}
																							}
																							else {
																								return 1;
																							}
																						}
																						else {
																							if ( Ay_squared <= -0.06) {
																								if ( Ax <= -0.53) {
																									return 0;
																								}
																								else {
																									return 1;
																								}
																							}
																							else {
																								if ( Ax_squared <= -0.1) {
																									if ( GxXGy <= 0.03) {
																										return 1;
																									}
																									else {
																										if ( AyXAz <= -0.26) {
																											return 0;
																										}
																										else {
																											return 0;
																										}
																									}
																								}
																								else {
																									return 0;
																								}
																							}
																						}
																					}
																					else {
																						if ( AyXGy <= -0.03) {
																							return 1;
																						}
																						else {
																							return 0;
																						}
																					}
																				}
																			}
																			else {
																				if ( Gz <= 0.36) {
																					if ( Gx <= -0.1) {
																						if ( Ax <= 0.4) {
																							return 0;
																						}
																						else {
																							return 1;
																						}
																					}
																					else {
																						if ( AzXGx <= 0.03) {
																							if ( AyXAz <= 0.05) {
																								if ( AxXGz <= 0.04) {
																									if ( AyXAz <= -0.02) {
																										return 1;
																									}
																									else {
																										return 1;
																									}
																								}
																								else {
																									return 1;
																								}
																							}
																							else {
																								return 1;
																							}
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																		}
																	}
																	else {
																		if ( Az <= 0.13) {
																			if ( Gy_squared <= -0.16) {
																				if ( Gz <= 0.75) {
																					if ( AxXGy <= 0.0) {
																						if ( Gz <= 0.55) {
																							if ( AxXGy <= 0.0) {
																								if ( AxXAz <= 0.02) {
																									return 0;
																								}
																								else {
																									if ( Gx <= 0.08) {
																										if ( AxXGy <= -0.0) {
																											return 1;
																										}
																										else {
																											return 1;
																										}
																									}
																									else {
																										return 1;
																									}
																								}
																							}
																							else {
																								return 1;
																							}
																						}
																						else {
																							if ( AyXGy <= 0.06) {
																								return 0;
																							}
																							else {
																								return 1;
																							}
																						}
																					}
																					else {
																						return 1;
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				if ( AzXGx <= -0.01) {
																					return 0;
																				}
																				else {
																					return 1;
																				}
																			}
																		}
																		else {
																			if ( Gx_squared <= -0.15) {
																				if ( Gz <= 0.43) {
																					return 0;
																				}
																				else {
																					if ( GyXGz <= -0.05) {
																						if ( AyXGx <= -0.05) {
																							return 1;
																						}
																						else {
																							if ( AzXGy <= -0.0) {
																								return 1;
																							}
																							else {
																								if ( AzXGx <= 0.01) {
																									return 0;
																								}
																								else {
																									return 0;
																								}
																							}
																						}
																					}
																					else {
																						if ( AyXGz <= 0.28) {
																							return 0;
																						}
																						else {
																							if ( AyXGz <= 0.31) {
																								return 0;
																							}
																							else {
																								return 1;
																							}
																						}
																					}
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																}
															}
															else {
																if ( Gy <= -0.12) {
																	return 1;
																}
																else {
																	if ( AyXGy <= 0.02) {
																		return 1;
																	}
																	else {
																		if ( AzXGy <= -0.13) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																}
															}
														}
													}
													else {
														if ( AxXGy <= -0.11) {
															return 1;
														}
														else {
															if ( Gy <= 0.14) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
												}
											}
											else {
												if ( Gx <= -0.22) {
													if ( Gx_squared <= -0.14) {
														if ( AxXGx <= -0.12) {
															if ( AyXGz <= 0.21) {
																if ( AxXGx <= -0.17) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( Ax <= -0.21) {
																if ( Gz <= 0.83) {
																	if ( Gy_squared <= -0.16) {
																		if ( AyXGz <= -0.03) {
																			if ( AzXGx <= 0.15) {
																				return 0;
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			if ( Az <= -0.05) {
																				if ( AyXGz <= 0.09) {
																					if ( AxXAz <= 0.02) {
																						return 1;
																					}
																					else {
																						if ( Gx <= -0.29) {
																							return 1;
																						}
																						else {
																							return 0;
																						}
																					}
																				}
																				else {
																					if ( GyXGz <= -0.02) {
																						if ( AzXGy <= -0.05) {
																							return 1;
																						}
																						else {
																							if ( AzXGy <= -0.0) {
																								return 0;
																							}
																							else {
																								return 1;
																							}
																						}
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																			else {
																				if ( AzXGz <= -0.02) {
																					return 0;
																				}
																				else {
																					return 0;
																				}
																			}
																		}
																	}
																	else {
																		if ( Gy_squared <= -0.14) {
																			if ( AyXGx <= -0.19) {
																				return 1;
																			}
																			else {
																				if ( Gz_squared <= -0.15) {
																					return 0;
																				}
																				else {
																					return 1;
																				}
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AyXGy <= -0.28) {
																	return 0;
																}
																else {
																	if ( Az_squared <= -0.02) {
																		if ( AyXGy <= 0.04) {
																			if ( Gx <= -0.28) {
																				if ( AxXAy <= 0.39) {
																					if ( Az <= -0.19) {
																						return 1;
																					}
																					else {
																						if ( Gx_squared <= -0.16) {
																							return 0;
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																				else {
																					if ( Ax <= 0.34) {
																						if ( Az <= -0.32) {
																							return 1;
																						}
																						else {
																							return 0;
																						}
																					}
																					else {
																						return 1;
																					}
																				}
																			}
																			else {
																				if ( GyXGz <= -0.04) {
																					return 1;
																				}
																				else {
																					return 1;
																				}
																			}
																		}
																		else {
																			if ( GxXGz <= -0.03) {
																				return 1;
																			}
																			else {
																				if ( Gx_squared <= -0.16) {
																					return 1;
																				}
																				else {
																					if ( Ay_squared <= -0.21) {
																						return 1;
																					}
																					else {
																						if ( AyXAz <= -0.57) {
																							return 1;
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																			}
																		}
																	}
																	else {
																		if ( Az_squared <= 0.46) {
																			if ( AzXGx <= 0.1) {
																				if ( AxXGx <= -0.04) {
																					return 1;
																				}
																				else {
																					return 1;
																				}
																			}
																			else {
																				if ( AxXGy <= 0.03) {
																					if ( AzXGy <= 0.08) {
																						if ( GxXGy <= 0.02) {
																							if ( AxXGx <= -0.08) {
																								return 1;
																							}
																							else {
																								return 1;
																							}
																						}
																						else {
																							return 1;
																						}
																					}
																					else {
																						return 1;
																					}
																				}
																				else {
																					return 1;
																				}
																			}
																		}
																		else {
																			return 0;
																		}
																	}
																}
															}
														}
													}
													else {
														if ( AzXGx <= 0.19) {
															if ( Ax_squared <= -0.07) {
																if ( AyXGy <= -0.25) {
																	return 1;
																}
																else {
																	if ( Gx <= -0.55) {
																		if ( AxXAz <= -0.01) {
																			return 1;
																		}
																		else {
																			return 0;
																		}
																	}
																	else {
																		if ( AxXGy <= -0.02) {
																			return 0;
																		}
																		else {
																			if ( AyXGz <= 0.33) {
																				return 1;
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																}
															}
															else {
																if ( AyXGz <= 0.0) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( Gy_squared <= -0.18) {
																return 1;
															}
															else {
																if ( Ay_squared <= -0.19) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( Az <= -0.96) {
														if ( AxXAy <= -0.14) {
															if ( Gy_squared <= -0.17) {
																if ( Ax_squared <= 0.01) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( Az <= -1.75) {
																return 0;
															}
															else {
																if ( Gy_squared <= -0.16) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( AxXGx <= -0.01) {
															if ( Ax_squared <= 0.01) {
																if ( Gy <= -0.07) {
																	if ( Gx <= -0.18) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
												}
											}
										}
									}
									else {
										if ( Ay <= 0.43) {
											if ( Gx <= 0.07) {
												if ( Gy <= -0.04) {
													return 0;
												}
												else {
													return 0;
												}
											}
											else {
												return 0;
											}
										}
										else {
											return 0;
										}
									}
								}
								else {
									if ( Ay_squared <= -0.29) {
										if ( Ay_squared <= -0.87) {
											if ( Gy_squared <= -0.17) {
												return 0;
											}
											else {
												return 0;
											}
										}
										else {
											return 0;
										}
									}
									else {
										return 1;
									}
								}
							}
						}
					}
				}
				else {
					if ( Gz <= -0.85) {
						if ( Gy_squared <= 1.33) {
							if ( GxXGz <= -0.4) {
								if ( AyXGx <= 0.55) {
									if ( Az_squared <= -0.15) {
										return 1;
									}
									else {
										if ( Gy <= -1.29) {
											return 1;
										}
										else {
											return 1;
										}
									}
								}
								else {
									return 1;
								}
							}
							else {
								if ( Gz_squared <= 0.51) {
									if ( AyXGy <= 0.13) {
										if ( Ax <= -0.92) {
											return 1;
										}
										else {
											if ( AxXAy <= 0.17) {
												if ( Gz <= -1.07) {
													if ( Gx_squared <= -0.04) {
														return 1;
													}
													else {
														return 0;
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( AyXGz <= 0.09) {
													if ( Ay <= 1.64) {
														if ( AzXGz <= 0.47) {
															if ( Gz <= -1.2) {
																return 1;
															}
															else {
																if ( AxXGx <= 0.08) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
										}
									}
									else {
										if ( Gy <= -0.95) {
											if ( Gx_squared <= -0.11) {
												return 1;
											}
											else {
												if ( GxXGz <= -0.31) {
													return 1;
												}
												else {
													if ( AxXGy <= -0.86) {
														return 1;
													}
													else {
														if ( AxXGx <= -0.04) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
											}
										}
										else {
											if ( AzXGz <= 0.25) {
												if ( Az_squared <= -0.21) {
													return 1;
												}
												else {
													if ( Ax_squared <= 0.13) {
														return 0;
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( Gz <= -1.13) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
									}
								}
								else {
									return 1;
								}
							}
						}
						else {
							return 1;
						}
					}
					else {
						if ( AyXGx <= -0.21) {
							if ( AxXGx <= 0.3) {
								if ( AzXGx <= -0.04) {
									if ( GxXGy <= -0.41) {
										return 1;
									}
									else {
										if ( Gz <= -0.05) {
											if ( GxXGz <= -0.12) {
												if ( AzXGx <= -0.28) {
													return 1;
												}
												else {
													if ( Gx <= 0.87) {
														return 0;
													}
													else {
														if ( Gz <= -0.64) {
															if ( Gx_squared <= -0.0) {
																return 0;
															}
															else {
																if ( AyXAz <= 0.25) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												if ( Gz_squared <= -0.14) {
													if ( Gz <= -0.22) {
														if ( Gx <= 0.6) {
															if ( Az_squared <= -0.13) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															if ( AxXAy <= -0.27) {
																return 1;
															}
															else {
																if ( Gy <= -0.31) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( AyXAz <= 0.47) {
															if ( AxXGz <= -0.02) {
																if ( GxXGy <= -0.16) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AzXGz <= 0.03) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( Gy <= -0.99) {
																if ( Gy <= -1.1) {
																	if ( AzXGy <= 0.59) {
																		return 1;
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gx <= 0.66) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( GxXGy <= -0.06) {
														if ( Gx_squared <= -0.09) {
															if ( AzXGz <= 0.12) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															if ( Ax_squared <= -0.09) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AyXAz <= 0.42) {
															if ( AzXGy <= 0.01) {
																if ( AxXGz <= -0.1) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( AzXGx <= -0.2) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
												}
											}
										}
										else {
											if ( AyXAz <= 0.67) {
												if ( Ax <= -0.4) {
													if ( Gz_squared <= -0.05) {
														if ( Ay_squared <= -0.31) {
															return 1;
														}
														else {
															if ( AzXGy <= 0.41) {
																if ( AyXGx <= -0.27) {
																	if ( AxXGz <= -0.04) {
																		return 1;
																	}
																	else {
																		if ( Gx <= 0.69) {
																			if ( GxXGy <= 0.06) {
																				if ( Gx <= 0.61) {
																					return 0;
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																		else {
																			if ( AzXGz <= -0.11) {
																				return 0;
																			}
																			else {
																				if ( GxXGz <= 0.05) {
																					return 0;
																				}
																				else {
																					return 1;
																				}
																			}
																		}
																	}
																}
																else {
																	if ( AyXGx <= -0.23) {
																		if ( Ay_squared <= -0.1) {
																			return 1;
																		}
																		else {
																			if ( AxXAy <= 0.21) {
																				if ( GxXGz <= 0.02) {
																					return 0;
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																	else {
																		return 0;
																	}
																}
															}
															else {
																if ( AzXGy <= 0.52) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( Gx_squared <= -0.1) {
														if ( AxXAz <= -0.05) {
															if ( Gy <= -0.18) {
																if ( AzXGy <= 0.4) {
																	if ( Gx_squared <= -0.11) {
																		return 0;
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( Gy_squared <= -0.05) {
																if ( AyXGx <= -0.3) {
																	return 0;
																}
																else {
																	if ( AyXGx <= -0.23) {
																		if ( AxXGx <= 0.05) {
																			if ( GxXGz <= 0.03) {
																				return 0;
																			}
																			else {
																				return 0;
																			}
																		}
																		else {
																			return 0;
																		}
																	}
																	else {
																		return 0;
																	}
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( AyXGy <= 0.63) {
															if ( Gx <= 0.76) {
																if ( Ax <= 0.05) {
																	if ( Ax <= -0.28) {
																		return 0;
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	if ( Gx_squared <= -0.07) {
																		if ( Gy_squared <= 0.01) {
																			return 1;
																		}
																		else {
																			if ( Ax <= 0.54) {
																				return 0;
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																	else {
																		return 1;
																	}
																}
															}
															else {
																if ( AyXGy <= 0.27) {
																	if ( AzXGx <= -0.2) {
																		return 1;
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( Ax <= 0.27) {
																if ( AxXAy <= 0.0) {
																	if ( Gz_squared <= -0.14) {
																		return 0;
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AzXGy <= 0.46) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
											}
											else {
												if ( AzXGy <= 0.44) {
													if ( AyXGz <= -0.2) {
														return 0;
													}
													else {
														if ( Gz <= 0.28) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( Ax_squared <= -0.05) {
														if ( Gy_squared <= 0.12) {
															if ( AzXGx <= -0.42) {
																return 0;
															}
															else {
																if ( GxXGy <= -0.19) {
																	if ( Gx_squared <= -0.06) {
																		if ( AzXGx <= -0.38) {
																			return 0;
																		}
																		else {
																			if ( Gy <= -1.08) {
																				return 0;
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
											}
										}
									}
								}
								else {
									if ( Gz_squared <= -0.0) {
										if ( Gz <= -0.17) {
											if ( Gx_squared <= 0.02) {
												if ( Az <= 1.39) {
													if ( AxXGy <= 0.05) {
														if ( AxXGy <= -0.01) {
															if ( Gz <= -0.29) {
																if ( GyXGz <= -0.04) {
																	return 1;
																}
																else {
																	if ( Gz_squared <= -0.14) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( GxXGy <= -0.09) {
												if ( Ax <= 0.8) {
													if ( AxXGy <= -0.02) {
														if ( AyXGz <= -0.22) {
															return 1;
														}
														else {
															if ( Az <= 1.02) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( Ax_squared <= 0.03) {
													if ( AyXGx <= -0.3) {
														if ( AyXAz <= -0.4) {
															return 1;
														}
														else {
															return 1;
														}
													}
													else {
														if ( Gz <= 0.01) {
															return 1;
														}
														else {
															if ( Ax_squared <= -0.05) {
																if ( AxXAy <= 0.24) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													return 1;
												}
											}
										}
									}
									else {
										return 0;
									}
								}
							}
							else {
								if ( Gx <= 1.01) {
									if ( AyXAz <= -0.39) {
										return 1;
									}
									else {
										if ( AzXGx <= -0.31) {
											if ( Az <= -1.09) {
												return 1;
											}
											else {
												return 1;
											}
										}
										else {
											if ( Gy <= -1.0) {
												if ( GxXGz <= 0.08) {
													if ( Gz <= -0.3) {
														return 1;
													}
													else {
														if ( Gx_squared <= -0.07) {
															if ( GxXGz <= -0.0) {
																return 0;
															}
															else {
																if ( AyXGx <= -0.27) {
																	if ( GxXGz <= 0.03) {
																		return 0;
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( AxXAz <= 0.05) {
													if ( Az <= -0.47) {
														return 1;
													}
													else {
														if ( AzXGy <= 0.05) {
															if ( AyXAz <= 0.27) {
																if ( AxXGz <= -0.2) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( AzXGx <= -0.18) {
																return 1;
															}
															else {
																if ( AxXAy <= -0.65) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													return 1;
												}
											}
										}
									}
								}
								else {
									if ( Gx_squared <= 0.04) {
										return 1;
									}
									else {
										return 1;
									}
								}
							}
						}
						else {
							if ( GxXGz <= 0.06) {
								if ( Gz_squared <= -0.15) {
									if ( Az_squared <= -0.14) {
										if ( Gz <= -0.02) {
											if ( AzXGz <= 0.04) {
												if ( Gx_squared <= -0.03) {
													if ( Az <= 0.94) {
														if ( AyXAz <= -0.26) {
															return 1;
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 1;
											}
										}
										else {
											if ( Gx_squared <= -0.07) {
												if ( AzXGz <= 0.01) {
													return 0;
												}
												else {
													return 1;
												}
											}
											else {
												if ( AyXAz <= -0.29) {
													if ( Az <= 0.07) {
														return 1;
													}
													else {
														if ( Gz_squared <= -0.15) {
															return 0;
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( AzXGx <= -0.03) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
										}
									}
									else {
										if ( Gx_squared <= 0.0) {
											if ( Ay <= -0.55) {
												return 0;
											}
											else {
												if ( Ax <= -0.28) {
													if ( Az_squared <= 0.51) {
														if ( GxXGz <= 0.02) {
															if ( GxXGy <= -0.03) {
																return 1;
															}
															else {
																if ( Gy_squared <= -0.16) {
																	if ( AyXGy <= 0.05) {
																		return 0;
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( Ax_squared <= 0.2) {
														if ( Gx_squared <= -0.1) {
															if ( GxXGy <= 0.01) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															if ( Az <= -0.44) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											return 1;
										}
									}
								}
								else {
									if ( Ay <= -0.46) {
										if ( Ay <= -0.71) {
											return 0;
										}
										else {
											if ( Ay <= -0.6) {
												if ( GxXGz <= -0.02) {
													return 1;
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
									}
									else {
										if ( Gz_squared <= -0.13) {
											if ( Ax <= -1.06) {
												return 0;
											}
											else {
												if ( Az <= -0.55) {
													if ( Ax <= -0.39) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													if ( Gx_squared <= -0.09) {
														if ( AxXAy <= 0.24) {
															if ( Az_squared <= -0.05) {
																return 1;
															}
															else {
																return 0;
															}
														}
														else {
															if ( Gx_squared <= -0.1) {
																if ( AxXGx <= 0.18) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( Gx_squared <= -0.08) {
															return 1;
														}
														else {
															if ( AxXGx <= 0.04) {
																return 1;
															}
															else {
																return 0;
															}
														}
													}
												}
											}
										}
										else {
											if ( GxXGy <= -0.08) {
												if ( AyXGx <= 0.39) {
													return 1;
												}
												else {
													return 1;
												}
											}
											else {
												if ( AxXAy <= 0.38) {
													if ( GxXGy <= 0.06) {
														if ( Gx_squared <= -0.07) {
															if ( AyXGz <= -0.27) {
																return 1;
															}
															else {
																if ( AyXAz <= -0.71) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
										}
									}
								}
							}
							else {
								if ( GxXGz <= 0.57) {
									if ( Ay_squared <= 0.47) {
										if ( AzXGx <= -0.33) {
											return 1;
										}
										else {
											if ( Ay <= 1.0) {
												return 1;
											}
											else {
												if ( Ay <= 1.12) {
													return 1;
												}
												else {
													if ( GyXGz <= -0.01) {
														if ( Ay_squared <= -0.27) {
															return 1;
														}
														else {
															if ( AyXGx <= 0.49) {
																if ( Ay <= 1.33) {
																	if ( Ay_squared <= -0.07) {
																		if ( AzXGx <= -0.11) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	if ( AxXGy <= 0.04) {
																		return 1;
																	}
																	else {
																		return 0;
																	}
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( Gz <= 0.79) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
											}
										}
									}
									else {
										return 1;
									}
								}
								else {
									return 1;
								}
							}
						}
					}
				}
			}
			else {
				if ( AzXGx <= -0.1) {
					if ( Gx_squared <= 0.36) {
						if ( Az <= -0.64) {
							if ( GxXGz <= 0.52) {
								if ( AxXGx <= 0.74) {
									if ( AzXGx <= -1.11) {
										return 1;
									}
									else {
										if ( AxXGx <= -0.02) {
											if ( AyXAz <= 0.53) {
												return 1;
											}
											else {
												if ( Gx_squared <= 0.25) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( Ax <= 0.54) {
												if ( AxXAy <= 0.38) {
													if ( Gy_squared <= 0.43) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
									}
								}
								else {
									return 1;
								}
							}
							else {
								return 1;
							}
						}
						else {
							if ( AzXGx <= -0.3) {
								if ( Ay <= 0.69) {
									if ( AyXGy <= 0.05) {
										return 1;
									}
									else {
										if ( GxXGz <= -0.33) {
											return 1;
										}
										else {
											if ( AzXGy <= 0.12) {
												return 1;
											}
											else {
												if ( Az <= -0.26) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
									}
								}
								else {
									if ( Ay_squared <= -0.04) {
										if ( GxXGz <= -0.47) {
											return 1;
										}
										else {
											return 1;
										}
									}
									else {
										if ( Az <= -0.16) {
											return 1;
										}
										else {
											return 1;
										}
									}
								}
							}
							else {
								if ( Gx <= -1.48) {
									return 1;
								}
								else {
									if ( Gy <= -0.92) {
										return 1;
									}
									else {
										if ( Gy <= -0.08) {
											if ( GxXGy <= -0.16) {
												return 1;
											}
											else {
												if ( Ay_squared <= 0.08) {
													if ( AzXGy <= 0.02) {
														return 1;
													}
													else {
														return 0;
													}
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( Gy <= 0.15) {
												return 1;
											}
											else {
												return 1;
											}
										}
									}
								}
							}
						}
					}
					else {
						if ( Ay_squared <= 0.72) {
							if ( Gz <= -1.75) {
								return 1;
							}
							else {
								if ( AzXGx <= -1.17) {
									return 1;
								}
								else {
									if ( Ay <= 0.6) {
										if ( Gy_squared <= 0.3) {
											if ( Gz <= 0.02) {
												return 1;
											}
											else {
												return 1;
											}
										}
										else {
											return 1;
										}
									}
									else {
										if ( Gz <= -1.09) {
											return 1;
										}
										else {
											return 1;
										}
									}
								}
							}
						}
						else {
							return 1;
						}
					}
				}
				else {
					if ( AyXGz <= -0.09) {
						if ( Gx <= 0.24) {
							if ( Gy <= -2.17) {
								return 1;
							}
							else {
								if ( Gy_squared <= -0.13) {
									if ( AyXAz <= 0.13) {
										if ( Gy <= 0.23) {
											if ( AzXGx <= 0.21) {
												return 1;
											}
											else {
												return 1;
											}
										}
										else {
											return 0;
										}
									}
									else {
										if ( AxXGz <= 0.36) {
											if ( Gy <= 0.22) {
												if ( AxXAy <= 0.27) {
													if ( AxXGz <= 0.14) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 0;
											}
										}
										else {
											return 1;
										}
									}
								}
								else {
									if ( AyXGx <= -0.06) {
										if ( AyXGz <= -0.39) {
											if ( Gy_squared <= 0.14) {
												return 1;
											}
											else {
												return 1;
											}
										}
										else {
											return 1;
										}
									}
									else {
										if ( GxXGy <= 0.56) {
											return 1;
										}
										else {
											return 1;
										}
									}
								}
							}
						}
						else {
							if ( AxXAy <= 0.16) {
								return 1;
							}
							else {
								return 1;
							}
						}
					}
					else {
						if ( Ay <= -0.38) {
							if ( Gx <= 0.8) {
								if ( AzXGx <= 0.85) {
									if ( Az <= 0.17) {
										if ( Gx <= -1.48) {
											if ( Gx_squared <= 0.44) {
												if ( GxXGz <= 0.59) {
													if ( AzXGz <= 0.06) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
										else {
											if ( GxXGy <= 0.43) {
												if ( Gz <= -0.51) {
													return 1;
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
									}
									else {
										if ( Az_squared <= -0.21) {
											return 1;
										}
										else {
											if ( Gx_squared <= 0.35) {
												return 1;
											}
											else {
												return 1;
											}
										}
									}
								}
								else {
									return 1;
								}
							}
							else {
								if ( Gy <= -2.71) {
									return 1;
								}
								else {
									if ( AzXGy <= -0.03) {
										return 1;
									}
									else {
										return 1;
									}
								}
							}
						}
						else {
							if ( GxXGz <= -1.35) {
								return 1;
							}
							else {
								if ( Gx <= -0.37) {
									if ( Gy_squared <= 2.04) {
										if ( AxXGy <= 0.43) {
											if ( Gx <= -1.93) {
												return 1;
											}
											else {
												if ( Az <= -1.03) {
													return 1;
												}
												else {
													if ( AzXGx <= 0.47) {
														if ( AyXGy <= -1.32) {
															return 1;
														}
														else {
															if ( Gz <= 1.48) {
																if ( AyXGy <= -0.32) {
																	if ( GxXGy <= 0.64) {
																		if ( Gx <= -1.38) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( Gy_squared <= -0.13) {
															return 1;
														}
														else {
															if ( AxXAz <= 0.07) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
												}
											}
										}
										else {
											return 1;
										}
									}
									else {
										return 1;
									}
								}
								else {
									return 1;
								}
							}
						}
					}
				}
			}
		}
		else {
			if ( Gx_squared <= 0.03) {
				if ( AzXGx <= -0.13) {
					if ( Gx <= 0.29) {
						if ( Gy_squared <= -0.05) {
							if ( AxXAy <= -0.15) {
								return 1;
							}
							else {
								return 0;
							}
						}
						else {
							if ( Az <= 0.39) {
								return 1;
							}
							else {
								return 1;
							}
						}
					}
					else {
						if ( AxXGx <= 0.61) {
							if ( Gx <= 0.37) {
								if ( Gz <= 0.45) {
									if ( Ay <= 0.01) {
										return 0;
									}
									else {
										return 1;
									}
								}
								else {
									return 1;
								}
							}
							else {
								if ( Ay <= 0.68) {
									if ( Gx_squared <= -0.14) {
										return 1;
									}
									else {
										if ( Gx_squared <= -0.08) {
											if ( GyXGz <= 0.52) {
												if ( Az <= -1.09) {
													return 1;
												}
												else {
													if ( Gz <= -1.04) {
														return 0;
													}
													else {
														if ( AxXGz <= 0.02) {
															if ( Ax <= 0.28) {
																if ( Ay_squared <= -0.05) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 1;
														}
													}
												}
											}
											else {
												return 1;
											}
										}
										else {
											if ( Gz <= -0.62) {
												return 1;
											}
											else {
												if ( Ax_squared <= 0.15) {
													if ( AyXGy <= -1.31) {
														return 1;
													}
													else {
														if ( Ay_squared <= 0.26) {
															if ( AxXGx <= 0.03) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
												}
												else {
													return 1;
												}
											}
										}
									}
								}
								else {
									if ( Gz <= -1.9) {
										return 1;
									}
									else {
										if ( Gx <= 0.59) {
											if ( GyXGz <= -0.06) {
												if ( AyXGx <= 0.31) {
													if ( AyXGz <= -0.4) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( AyXGx <= 0.24) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( Gy <= 1.78) {
												if ( Gx_squared <= -0.1) {
													return 1;
												}
												else {
													if ( Az <= -0.24) {
														if ( AzXGz <= -0.25) {
															return 1;
														}
														else {
															if ( AzXGy <= -0.27) {
																if ( GxXGz <= -0.3) {
																	return 1;
																}
																else {
																	if ( AxXGy <= 0.13) {
																		if ( Gz <= -0.54) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		return 1;
																	}
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( Az_squared <= -0.14) {
															return 1;
														}
														else {
															if ( AyXGx <= 0.52) {
																if ( Ay_squared <= -0.28) {
																	return 1;
																}
																else {
																	if ( AyXGy <= 0.45) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
															}
															else {
																return 1;
															}
														}
													}
												}
											}
											else {
												if ( AxXAz <= 0.08) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
									}
								}
							}
						}
						else {
							return 1;
						}
					}
				}
				else {
					if ( AyXGy <= -2.02) {
						if ( GxXGy <= 0.27) {
							if ( Gz <= -1.16) {
								return 1;
							}
							else {
								return 1;
							}
						}
						else {
							return 1;
						}
					}
					else {
						if ( AyXGy <= 0.09) {
							if ( AxXAy <= -0.82) {
								if ( Az <= 0.15) {
									if ( Gx <= -0.46) {
										return 1;
									}
									else {
										if ( AxXAy <= -1.02) {
											return 1;
										}
										else {
											if ( Ay <= -0.62) {
												return 1;
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									if ( GxXGy <= 0.19) {
										if ( AxXGy <= 0.6) {
											if ( AxXGy <= 0.41) {
												if ( Gx <= -0.3) {
													return 1;
												}
												else {
													return 1;
												}
											}
											else {
												if ( AxXGx <= 0.07) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
										else {
											return 1;
										}
									}
									else {
										return 1;
									}
								}
							}
							else {
								if ( Gz <= 0.81) {
									if ( AyXAz <= -0.04) {
										if ( Gz <= -0.85) {
											if ( AyXAz <= -0.48) {
												return 0;
											}
											else {
												if ( AyXAz <= -0.32) {
													return 0;
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( AyXGx <= -0.14) {
												if ( GyXGz <= 0.06) {
													if ( Gx <= 0.54) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( Ax <= 0.12) {
													if ( AyXGy <= -0.5) {
														return 1;
													}
													else {
														if ( Gz_squared <= -0.14) {
															if ( Gz_squared <= -0.15) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( Gx <= 0.01) {
														if ( AxXAz <= 0.07) {
															return 1;
														}
														else {
															if ( AzXGz <= 0.01) {
																return 1;
															}
															else {
																if ( GxXGy <= -0.1) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														return 1;
													}
												}
											}
										}
									}
									else {
										if ( AzXGx <= 0.04) {
											if ( AzXGz <= 0.11) {
												if ( AyXGz <= 0.62) {
													if ( AyXAz <= 0.59) {
														if ( AyXAz <= 0.39) {
															if ( AyXGx <= -0.25) {
																if ( GyXGz <= 0.0) {
																	if ( GxXGy <= 0.19) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AyXAz <= 0.13) {
																	if ( AxXAy <= 0.38) {
																		if ( AxXAy <= -0.46) {
																			if ( GxXGy <= 0.06) {
																				if ( AxXAy <= -0.53) {
																					return 1;
																				}
																				else {
																					return 1;
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			if ( GyXGz <= 0.08) {
																				if ( AxXGy <= 0.03) {
																					return 1;
																				}
																				else {
																					if ( AyXGx <= -0.18) {
																						return 1;
																					}
																					else {
																						if ( AxXGy <= 0.07) {
																							return 0;
																						}
																						else {
																							if ( Gx <= 0.24) {
																								if ( Ay_squared <= -0.18) {
																									return 1;
																								}
																								else {
																									return 1;
																								}
																							}
																							else {
																								return 0;
																							}
																						}
																					}
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	if ( AxXGz <= -0.08) {
																		return 0;
																	}
																	else {
																		if ( GyXGz <= 0.08) {
																			if ( Ay_squared <= -0.36) {
																				return 1;
																			}
																			else {
																				if ( AxXGx <= -0.02) {
																					return 0;
																				}
																				else {
																					if ( GxXGz <= -0.01) {
																						return 1;
																					}
																					else {
																						if ( Ax <= -0.22) {
																							if ( AyXAz <= 0.35) {
																								return 0;
																							}
																							else {
																								return 1;
																							}
																						}
																						else {
																							if ( GyXGz <= 0.03) {
																								if ( AxXAy <= -0.38) {
																									return 0;
																								}
																								else {
																									if ( GxXGy <= 0.06) {
																										return 1;
																									}
																									else {
																										return 1;
																									}
																								}
																							}
																							else {
																								return 1;
																							}
																						}
																					}
																				}
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																}
															}
														}
														else {
															if ( AyXGz <= 0.03) {
																if ( Gy_squared <= -0.05) {
																	if ( Gz_squared <= -0.14) {
																		return 0;
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Gz <= -0.14) {
																	if ( Az <= -0.28) {
																		if ( Gz_squared <= -0.15) {
																			if ( Ay <= -0.64) {
																				if ( AzXGx <= -0.05) {
																					return 0;
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( GyXGz <= 0.01) {
															if ( AxXGy <= 0.03) {
																if ( Gz_squared <= -0.15) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gz <= -0.01) {
																	if ( GyXGz <= -0.06) {
																		if ( Az_squared <= 0.2) {
																			if ( Gz <= -0.21) {
																				return 0;
																			}
																			else {
																				return 0;
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		if ( AxXAy <= -0.01) {
																			return 0;
																		}
																		else {
																			return 0;
																		}
																	}
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 1;
														}
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( AzXGz <= 0.4) {
													if ( Gx_squared <= -0.15) {
														if ( AxXAz <= 0.1) {
															if ( Gy <= 0.98) {
																if ( Az_squared <= 0.37) {
																	if ( Gz <= -1.59) {
																		return 0;
																	}
																	else {
																		if ( AyXAz <= 0.5) {
																			return 1;
																		}
																		else {
																			if ( Ax_squared <= 0.02) {
																				if ( Az_squared <= 0.21) {
																					if ( AyXGx <= -0.06) {
																						return 0;
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( AzXGx <= -0.03) {
															if ( AzXGx <= -0.11) {
																return 1;
															}
															else {
																if ( AzXGz <= 0.26) {
																	if ( AyXGz <= 0.68) {
																		return 0;
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( AyXGy <= -0.66) {
												if ( Gy <= 2.12) {
													if ( Gx <= -0.8) {
														return 1;
													}
													else {
														if ( Gx_squared <= -0.1) {
															if ( GyXGz <= -0.46) {
																return 1;
															}
															else {
																if ( AzXGx <= 0.15) {
																	if ( GxXGy <= -0.18) {
																		return 1;
																	}
																	else {
																		if ( Ax_squared <= -0.1) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 1;
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( AzXGy <= -0.43) {
													if ( Ay <= -0.34) {
														if ( AyXGx <= 0.2) {
															if ( GxXGz <= 0.0) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( Gz <= -0.66) {
														return 1;
													}
													else {
														if ( AxXGy <= 0.04) {
															if ( Az_squared <= 0.17) {
																if ( AyXGz <= -0.26) {
																	return 0;
																}
																else {
																	if ( GxXGz <= -0.03) {
																		return 0;
																	}
																	else {
																		if ( Gy_squared <= -0.09) {
																			if ( AzXGx <= 0.17) {
																				if ( Gx <= -0.45) {
																					return 1;
																				}
																				else {
																					return 0;
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																}
															}
															else {
																if ( Ay_squared <= -0.24) {
																	if ( AxXGx <= -0.01) {
																		return 0;
																	}
																	else {
																		return 0;
																	}
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( Ax <= 1.59) {
																if ( AxXAz <= -0.3) {
																	if ( Az_squared <= 0.39) {
																		return 0;
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	if ( Gz_squared <= -0.09) {
																		if ( Az_squared <= -0.11) {
																			if ( AyXAz <= 0.12) {
																				return 1;
																			}
																			else {
																				if ( AxXGx <= -0.11) {
																					if ( Gx_squared <= -0.12) {
																						return 1;
																					}
																					else {
																						return 1;
																					}
																				}
																				else {
																					if ( Ay <= -0.68) {
																						return 1;
																					}
																					else {
																						return 1;
																					}
																				}
																			}
																		}
																		else {
																			if ( Gx <= -0.28) {
																				if ( Gz_squared <= -0.14) {
																					if ( Ax_squared <= -0.08) {
																						return 1;
																					}
																					else {
																						if ( Gy <= 0.74) {
																							return 0;
																						}
																						else {
																							return 1;
																						}
																					}
																				}
																				else {
																					return 1;
																				}
																			}
																			else {
																				if ( AxXGz <= -0.06) {
																					return 1;
																				}
																				else {
																					return 1;
																				}
																			}
																		}
																	}
																	else {
																		return 0;
																	}
																}
															}
															else {
																return 1;
															}
														}
													}
												}
											}
										}
									}
								}
								else {
									if ( AyXGx <= -0.32) {
										return 1;
									}
									else {
										if ( AyXGy <= -0.9) {
											if ( AzXGx <= 0.25) {
												if ( AxXGx <= 0.02) {
													if ( Gx <= -0.04) {
														if ( AxXGx <= -0.13) {
															return 1;
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
										else {
											if ( AyXGy <= -0.56) {
												if ( AxXAy <= 0.22) {
													if ( AyXAz <= -0.06) {
														return 1;
													}
													else {
														if ( Ax <= 0.15) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( AyXAz <= 0.31) {
													if ( Ay_squared <= 0.29) {
														if ( GxXGz <= -0.03) {
															return 0;
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( AyXGy <= -0.3) {
														if ( AxXGy <= 0.22) {
															return 1;
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
											}
										}
									}
								}
							}
						}
						else {
							if ( AyXAz <= -0.48) {
								if ( Az <= -0.32) {
									if ( Gx <= 0.06) {
										if ( GxXGy <= -0.1) {
											if ( AzXGz <= -0.43) {
												return 1;
											}
											else {
												if ( AzXGx <= 0.26) {
													return 1;
												}
												else {
													if ( AxXGz <= -0.19) {
														return 1;
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( Gz <= -1.7) {
												return 1;
											}
											else {
												if ( Ax <= 1.06) {
													if ( Az <= -1.32) {
														return 1;
													}
													else {
														if ( AxXGz <= -0.24) {
															return 1;
														}
														else {
															if ( AyXAz <= -0.77) {
																return 1;
															}
															else {
																if ( GxXGy <= -0.01) {
																	if ( Az <= -0.62) {
																		return 1;
																	}
																	else {
																		if ( AxXAz <= -0.04) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																}
																else {
																	if ( AzXGz <= -0.03) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
															}
														}
													}
												}
												else {
													return 1;
												}
											}
										}
									}
									else {
										if ( Gy <= 0.71) {
											return 1;
										}
										else {
											if ( Az_squared <= 0.02) {
												if ( Ay_squared <= 0.09) {
													if ( Az_squared <= -0.03) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( AyXAz <= -0.93) {
													return 1;
												}
												else {
													if ( GxXGy <= 0.09) {
														return 1;
													}
													else {
														return 1;
													}
												}
											}
										}
									}
								}
								else {
									if ( GxXGy <= 0.07) {
										if ( Ay_squared <= -0.01) {
											if ( Az_squared <= -0.09) {
												return 1;
											}
											else {
												if ( GxXGz <= -0.0) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( AzXGz <= 0.14) {
												return 1;
											}
											else {
												return 1;
											}
										}
									}
									else {
										if ( AxXGz <= -0.27) {
											return 1;
										}
										else {
											if ( Az <= -0.16) {
												return 1;
											}
											else {
												return 1;
											}
										}
									}
								}
							}
							else {
								if ( Gz_squared <= 1.99) {
									if ( Gy <= 0.58) {
										return 1;
									}
									else {
										if ( Ax_squared <= 0.14) {
											if ( AxXGz <= 0.01) {
												if ( Gx_squared <= -0.04) {
													if ( AyXGy <= 0.54) {
														if ( Gy <= 0.64) {
															if ( AyXGx <= 0.13) {
																return 1;
															}
															else {
																return 0;
															}
														}
														else {
															if ( AzXGz <= -0.14) {
																return 0;
															}
															else {
																if ( Gy <= 0.78) {
																	if ( GxXGy <= -0.01) {
																		return 1;
																	}
																	else {
																		if ( AxXGy <= -0.05) {
																			return 1;
																		}
																		else {
																			if ( AyXAz <= -0.02) {
																				if ( AxXAz <= -0.08) {
																					return 1;
																				}
																				else {
																					if ( Az_squared <= -0.19) {
																						return 1;
																					}
																					else {
																						return 0;
																					}
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																	}
																}
																else {
																	if ( AyXGz <= -0.38) {
																		return 1;
																	}
																	else {
																		if ( AxXGx <= 0.01) {
																			if ( Gx_squared <= -0.15) {
																				if ( AyXGy <= 0.5) {
																					return 1;
																				}
																				else {
																					return 1;
																				}
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																}
															}
														}
													}
													else {
														if ( AyXGx <= -0.02) {
															return 1;
														}
														else {
															if ( Gx <= 0.17) {
																return 1;
															}
															else {
																if ( Gx <= 0.75) {
																	if ( AxXGy <= 0.38) {
																		if ( Gz <= -0.11) {
																			if ( Gz <= -0.87) {
																				return 1;
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( GxXGy <= 0.18) {
													if ( Ax <= 0.86) {
														if ( Az <= 0.7) {
															if ( AzXGx <= -0.08) {
																return 1;
															}
															else {
																if ( Ax <= -0.36) {
																	return 1;
																}
																else {
																	if ( Ax <= 0.49) {
																		if ( Gx <= 0.15) {
																			if ( Ay <= 1.05) {
																				return 0;
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		return 1;
																	}
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( AyXGx <= 0.35) {
												if ( AxXAy <= 0.81) {
													return 1;
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
									}
								}
								else {
									return 1;
								}
							}
						}
					}
				}
			}
			else {
				if ( Gx_squared <= 0.51) {
					if ( GxXGy <= 0.41) {
						if ( AyXGx <= -0.35) {
							if ( Ay_squared <= 0.36) {
								if ( AyXGx <= -0.9) {
									return 1;
								}
								else {
									if ( GyXGz <= 0.02) {
										if ( Az <= 0.06) {
											if ( Ay <= 1.18) {
												return 1;
											}
											else {
												return 1;
											}
										}
										else {
											return 1;
										}
									}
									else {
										if ( Gx <= -1.09) {
											return 1;
										}
										else {
											return 1;
										}
									}
								}
							}
							else {
								return 1;
							}
						}
						else {
							if ( AzXGx <= -0.3) {
								if ( AxXGx <= -0.06) {
									return 1;
								}
								else {
									if ( AzXGz <= 0.5) {
										if ( AzXGz <= 0.15) {
											return 1;
										}
										else {
											return 1;
										}
									}
									else {
										return 1;
									}
								}
							}
							else {
								if ( Gx <= 0.94) {
									if ( AzXGx <= 0.23) {
										if ( AzXGy <= -0.21) {
											return 1;
										}
										else {
											if ( GxXGy <= -0.3) {
												if ( AyXAz <= 0.01) {
													return 1;
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
									}
									else {
										if ( AzXGz <= 1.0) {
											if ( GxXGy <= -0.37) {
												if ( Gx <= -1.6) {
													if ( Gz <= 2.6) {
														if ( AxXGx <= 0.35) {
															return 1;
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( Gx <= -1.51) {
														return 1;
													}
													else {
														if ( GxXGy <= -0.53) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
											}
											else {
												if ( AzXGz <= -0.55) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
										else {
											return 1;
										}
									}
								}
								else {
									if ( Gz <= -0.27) {
										if ( GxXGz <= -0.35) {
											return 0;
										}
										else {
											return 1;
										}
									}
									else {
										return 1;
									}
								}
							}
						}
					}
					else {
						if ( AyXGx <= -0.01) {
							if ( Gx <= 1.18) {
								return 1;
							}
							else {
								if ( Gy_squared <= 0.57) {
									if ( Ax <= 0.65) {
										if ( AzXGx <= -0.29) {
											if ( Gy <= 1.16) {
												return 1;
											}
											else {
												return 1;
											}
										}
										else {
											return 1;
										}
									}
									else {
										return 1;
									}
								}
								else {
									if ( Gy_squared <= 1.94) {
										return 1;
									}
									else {
										return 1;
									}
								}
							}
						}
						else {
							if ( GyXGz <= 0.65) {
								if ( GxXGz <= 0.11) {
									if ( Gx_squared <= 0.23) {
										if ( AyXGz <= -0.84) {
											return 1;
										}
										else {
											if ( Gz_squared <= 0.03) {
												if ( AxXGy <= 0.2) {
													return 1;
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
									}
									else {
										if ( Gx <= 1.75) {
											if ( GxXGz <= -0.5) {
												return 0;
											}
											else {
												return 1;
											}
										}
										else {
											return 1;
										}
									}
								}
								else {
									if ( GyXGz <= 0.22) {
										return 1;
									}
									else {
										return 1;
									}
								}
							}
							else {
								return 1;
							}
						}
					}
				}
				else {
					if ( Gx <= 1.56) {
						if ( Gx_squared <= 0.55) {
							return 1;
						}
						else {
							if ( Gz <= 1.77) {
								return 1;
							}
							else {
								return 1;
							}
						}
					}
					else {
						if ( Gz <= 2.31) {
							if ( GxXGz <= -0.9) {
								return 1;
							}
							else {
								if ( AyXGy <= -0.45) {
									return 1;
								}
								else {
									if ( GyXGz <= 0.1) {
										return 1;
									}
									else {
										return 1;
									}
								}
							}
						}
						else {
							return 1;
						}
					}
				}
			}
		}
	}
	else {
		if ( Ax <= -1.83) {
			if ( Ay <= 0.18) {
				if ( Gx_squared <= 9.18) {
					if ( Ax <= -3.3) {
						if ( GyXGz <= 2.44) {
							if ( Gy_squared <= 1.88) {
								return 1;
							}
							else {
								return 1;
							}
						}
						else {
							return 0;
						}
					}
					else {
						if ( Gy_squared <= 2.97) {
							if ( Gy <= -1.56) {
								return 1;
							}
							else {
								if ( Gy_squared <= 1.11) {
									if ( Ax_squared <= 0.33) {
										return 1;
									}
									else {
										return 1;
									}
								}
								else {
									return 1;
								}
							}
						}
						else {
							return 1;
						}
					}
				}
				else {
					return 1;
				}
			}
			else {
				if ( GxXGz <= 12.05) {
					if ( Gx <= -5.96) {
						return 1;
					}
					else {
						if ( GxXGz <= -2.03) {
							return 1;
						}
						else {
							if ( Gz_squared <= -0.09) {
								return 1;
							}
							else {
								if ( AyXGx <= 3.34) {
									return 1;
								}
								else {
									return 1;
								}
							}
						}
					}
				}
				else {
					return 1;
				}
			}
		}
		else {
			if ( Gy <= -3.56) {
				if ( Gz <= -3.61) {
					if ( GyXGz <= 9.55) {
						return 1;
					}
					else {
						return 0;
					}
				}
				else {
					if ( Az_squared <= 4.39) {
						if ( GxXGy <= 7.45) {
							if ( AyXGx <= -3.81) {
								return 1;
							}
							else {
								if ( Az <= 0.25) {
									if ( AxXAy <= -0.7) {
										return 1;
									}
									else {
										return 1;
									}
								}
								else {
									return 1;
								}
							}
						}
						else {
							return 1;
						}
					}
					else {
						return 1;
					}
				}
			}
			else {
				if ( Ay <= -0.44) {
					if ( Gz <= 1.17) {
						if ( AxXGy <= -0.31) {
							if ( Gz <= -2.65) {
								return 1;
							}
							else {
								if ( AxXGx <= 0.75) {
									return 1;
								}
								else {
									return 1;
								}
							}
						}
						else {
							if ( Az <= -0.99) {
								if ( Gz <= -1.95) {
									return 1;
								}
								else {
									if ( Gy <= -2.0) {
										return 1;
									}
									else {
										if ( AzXGx <= -1.06) {
											return 1;
										}
										else {
											return 1;
										}
									}
								}
							}
							else {
								if ( Gx <= -1.93) {
									if ( Gy <= -0.72) {
										if ( Gy <= -1.7) {
											return 1;
										}
										else {
											return 1;
										}
									}
									else {
										if ( GyXGz <= -0.46) {
											return 1;
										}
										else {
											if ( GyXGz <= 0.27) {
												if ( GxXGz <= 0.92) {
													if ( Ay <= -1.13) {
														return 1;
													}
													else {
														if ( GyXGz <= 0.05) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
									}
								}
								else {
									if ( Gy <= 1.47) {
										if ( Gz_squared <= -0.11) {
											return 1;
										}
										else {
											if ( Gz <= -3.3) {
												return 1;
											}
											else {
												if ( GxXGy <= -0.12) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
									}
									else {
										return 1;
									}
								}
							}
						}
					}
					else {
						if ( Gz_squared <= 7.88) {
							if ( AyXGx <= 1.51) {
								if ( AyXAz <= 1.54) {
									if ( Gx <= 2.02) {
										return 1;
									}
									else {
										if ( Gy <= 0.78) {
											return 1;
										}
										else {
											return 1;
										}
									}
								}
								else {
									return 1;
								}
							}
							else {
								if ( AyXGx <= 6.25) {
									if ( GxXGz <= -1.09) {
										if ( Gz <= 3.93) {
											if ( Ay <= -1.72) {
												return 1;
											}
											else {
												if ( Ax <= -0.11) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
										else {
											return 1;
										}
									}
									else {
										return 1;
									}
								}
								else {
									return 1;
								}
							}
						}
						else {
							return 1;
						}
					}
				}
				else {
					if ( AxXGz <= -0.99) {
						if ( GxXGy <= -4.02) {
							return 1;
						}
						else {
							if ( AzXGx <= 3.83) {
								if ( AxXGz <= -2.81) {
									return 1;
								}
								else {
									return 1;
								}
							}
							else {
								return 1;
							}
						}
					}
					else {
						if ( Gx_squared <= 1.69) {
							if ( Gx_squared <= 0.82) {
								if ( AxXAy <= 0.11) {
									return 1;
								}
								else {
									return 1;
								}
							}
							else {
								if ( AyXGz <= -0.39) {
									if ( Gx <= -2.22) {
										return 1;
									}
									else {
										return 1;
									}
								}
								else {
									if ( Ax <= 1.97) {
										if ( AxXGy <= -0.64) {
											return 1;
										}
										else {
											if ( Az <= -2.04) {
												return 1;
											}
											else {
												if ( AxXAz <= -0.28) {
													return 1;
												}
												else {
													if ( Ax <= 0.09) {
														if ( Gz_squared <= 0.09) {
															if ( AxXGy <= -0.01) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
											}
										}
									}
									else {
										return 1;
									}
								}
							}
						}
						else {
							if ( Gz_squared <= 1.77) {
								if ( Gz_squared <= 0.33) {
									if ( Gz_squared <= -0.01) {
										if ( AyXGx <= 0.66) {
											if ( AxXGz <= -0.04) {
												return 1;
											}
											else {
												return 1;
											}
										}
										else {
											return 1;
										}
									}
									else {
										if ( Gz_squared <= 0.25) {
											if ( Ay <= 2.22) {
												return 1;
											}
											else {
												return 0;
											}
										}
										else {
											return 1;
										}
									}
								}
								else {
									if ( Gz_squared <= 1.14) {
										if ( AxXGz <= -0.29) {
											return 1;
										}
										else {
											return 1;
										}
									}
									else {
										return 1;
									}
								}
							}
							else {
								return 1;
							}
						}
					}
				}
			}
		}
	}
}
