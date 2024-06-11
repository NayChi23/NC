#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COLS 7
#define MAX_ROWS 2 //180 for the estrus and it will take 18 round to get one data which is equalivalent to 4 hours
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

int Health(float,float,float,float,float,float);
int CompareData(int, int, int);

int main(){
    unsigned int numberZero =0; //only reset to 0 if the data are equal to one day
    unsigned int numberOne =0;  //Store how many 1's in the data
    unsigned int num=0;
    bool FirstTurn = 1;
    unsigned int check_First_two_day = 0;
    //unsigned long int total_one_day_count[3] = {0,0,0};
    struct CircularQueue* total_one_day_count = createQueue(MAX_SIZE);
    struct Node* result_data = NULL;

    while(1){
        //For this i would like to use cicular queue for pushing the data 240 data
        char field[MAX_ROWS][MAX_COLS][MAX_FIELD_LENGTH] = {
            {"15:34:52,-0.10,0.01,0.86,50.88,-10.02,-4.12"},
            {"15:34:52,-0.05,-0.17,0.79,-21.53,-23.01,21.22"}
            //May be add the number later according to the data
        };
        if(num == 108 && FirstTurn  == 1)
        {
            //need condition to put it into the double linked list array
            enqueue(total_one_day_count,numberOne);
            printf("the total number one is %d\n", numberOne);
            numberOne = 0 ;
            numberZero = 0 ;
            num = 0;
            check_First_two_day += 1;
            printf("Complete %d turn \n", check_First_two_day);
            printQueue(total_one_day_count);
            
            if(check_First_two_day == 3)
            {
                FirstTurn = 0;
                printf("The result of compared data is\t%d\n",CompareData(indexFinding(total_one_day_count,0),indexFinding(total_one_day_count,1),indexFinding(total_one_day_count,2)));
                insertAtEnd(&result_data, CompareData(indexFinding(total_one_day_count,0),indexFinding(total_one_day_count,1),indexFinding(total_one_day_count,2)));
                printf("%d\n",indexFinding(total_one_day_count,0));
                printf("%d\n",indexFinding(total_one_day_count,1));
                printf("%d\n",indexFinding(total_one_day_count,2));
            }
            
        }        
        else if(num == 108 && FirstTurn  == 0){
            dequeue(total_one_day_count);
            printQueue(total_one_day_count);
            enqueue(total_one_day_count,numberOne);
            printQueue(total_one_day_count);
            printf("The result of compared data is\t%d\n",CompareData(indexFinding(total_one_day_count,0),indexFinding(total_one_day_count,1),indexFinding(total_one_day_count,2)));
            insertAtEnd(&result_data, CompareData(indexFinding(total_one_day_count,0),indexFinding(total_one_day_count,1),indexFinding(total_one_day_count,2)));
            printf("%d\n",indexFinding(total_one_day_count,0));
            printf("%d\n",indexFinding(total_one_day_count,1));
            printf("%d\n",indexFinding(total_one_day_count,2));
            numberOne = 0 ;
            numberZero = 0 ;
            num = 0;
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
            if (Health(ax,ay,az,gx,gy,gz)==1)
            {
                numberOne = numberOne +1;
            }
            else{
                numberZero = numberZero +1;
            }
            
        }
        num +=1;
        //printf("row number is %u\n",row);
        printf("the total loop number is %u\n",num);
        }
    }
    return 0;
}

int CompareData(int firstDay, int secondDay, int thirdDay) {
  if (firstDay > (secondDay + (0.1 * secondDay))) {  // 10% more
    if (secondDay > (thirdDay + (0.1 * thirdDay))) {
      return 1; //health problem
    } else {
      return -1; //Warning
    }
  } else {
    return 0; //OK
    //But have to ask the condition first
  }
}
int Health(float Ax,float Ay,float Az,float Gx,float Gy,float Gz )
{
    float AxXGx = Ax*Gx,AyXAz = Ay*Az,AxXGy = Ax*Gy,AxXGz = Ax*Gz,AxXAy = Ax*Ay,AxXAz = Ax*Az,AyXAx = Ay*Ax,AyXGx = Ay*Gx,AyXGy=Ay*Gy,AyXGz = Ay*Gz,AzXAx = Az*Ax,AzXAy = Az*Ay,AzXGx = Az*Gx,AzxGy = Az*Gy,AzXGz =Az*Gz,Ax_squared = Ax*Ax, Ay_squared = Ay*Ay, Az_squared = Az*Az,Gx_squared = Gx*Gx, Gy_squared = Gy*Gy, Gz_squared = Gz*Gz,GxXGz=Gx*Gz,GxXGy=Gx*Gy,GyXGz=Gy*Gz,AzXGy=Az*Gy;
	if ( Gy_squared <= -0.13) {
		if ( Gz <= -0.62) {
			if ( Gz <= -1.48) {
				if ( AyXGy <= -0.0) {
					if ( AyXGz <= -0.79) {
						return 0;
					}
					else {
						return 0;
					}
				}
				else {
					if ( AyXGz <= -0.82) {
						return 0;
					}
					else {
						return 0;
					}
				}
			}
			else {
				if ( Ax_squared <= -0.13) {
					if ( AyXGz <= -0.21) {
						if ( Ay <= 1.51) {
							if ( Gx_squared <= -0.12) {
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
						if ( GxXGz <= -0.16) {
							return 1;
						}
						else {
							if ( AxXAy <= 0.13) {
								return 0;
							}
							else {
								if ( Gz <= -0.8) {
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
					if ( AzXGx <= 0.11) {
						if ( AyXGy <= 0.05) {
							if ( Gz <= -0.88) {
								if ( AxXAz <= 0.0) {
									return 0;
								}
								else {
									return 0;
								}
							}
							else {
								if ( AyXGx <= -0.04) {
									if ( AyXGz <= 0.35) {
										return 0;
									}
									else {
										return 0;
									}
								}
								else {
									if ( AyXGx <= 0.09) {
										return 0;
									}
									else {
										return 0;
									}
								}
							}
						}
						else {
							if ( GxXGy <= -0.04) {
								return 1;
							}
							else {
								if ( AyXAz <= 0.6) {
									if ( AxXGx <= -0.02) {
										return 0;
									}
									else {
										if ( AxXAy <= 0.39) {
											if ( AzXGx <= -0.02) {
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
									return 1;
								}
							}
						}
					}
					else {
						if ( AzXGz <= 0.21) {
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
			if ( Ay <= -0.59) {
				if ( GxXGz <= 0.01) {
					if ( Gx <= -0.76) {
						if ( Az_squared <= -0.22) {
							if ( AxXAy <= -0.28) {
								if ( Gx_squared <= 0.04) {
									if ( Gz_squared <= -0.0) {
										if ( AzXGz <= -0.06) {
											return 1;
										}
										else {
											if ( AxXAz <= 0.08) {
												if ( AxXAy <= -0.5) {
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
										return 0;
									}
								}
								else {
									return 0;
								}
							}
							else {
								if ( AyXAz <= -0.19) {
									return 1;
								}
								else {
									if ( AyXGx <= 0.5) {
										return 0;
									}
									else {
										if ( Gx_squared <= 0.01) {
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
							if ( Ay_squared <= 0.3) {
								if ( AzXGz <= -0.38) {
									return 0;
								}
								else {
									if ( AzXGx <= 0.4) {
										if ( AxXAz <= 0.09) {
											if ( AxXGy <= 0.03) {
												if ( Az <= 0.07) {
													if ( Gy <= -0.05) {
														return 1;
													}
													else {
														if ( Ay_squared <= 0.08) {
															if ( AyXAz <= 0.39) {
																return 1;
															}
															else {
																if ( AxXGz <= 0.09) {
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
													if ( Gx_squared <= -0.03) {
														return 1;
													}
													else {
														if ( Gx_squared <= 0.04) {
															if ( Gz <= 0.78) {
																return 1;
															}
															else {
																if ( AxXAz <= 0.03) {
																	if ( Ay <= -0.7) {
																		if ( Gy_squared <= -0.16) {
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
											}
											else {
												return 1;
											}
										}
										else {
											if ( Gx <= -1.06) {
												return 0;
											}
											else {
												if ( GxXGz <= -0.17) {
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
								return 0;
							}
						}
					}
					else {
						if ( Az_squared <= -0.2) {
							if ( AxXGy <= -0.02) {
								if ( AyXGx <= -0.05) {
									if ( AyXGz <= 0.06) {
										return 1;
									}
									else {
										if ( AxXGx <= 0.08) {
											return 0;
										}
										else {
											if ( AxXAz <= 0.05) {
												return 0;
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									if ( Gz <= -0.26) {
										return 1;
									}
									else {
										if ( Gz <= 0.54) {
											if ( Gz <= 0.2) {
												if ( AyXAz <= 0.01) {
													if ( AxXGy <= -0.06) {
														return 0;
													}
													else {
														if ( AzXGy <= -0.02) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( GyXGz <= -0.03) {
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
							}
							else {
								if ( AyXAz <= -0.32) {
									if ( GxXGz <= 0.0) {
										if ( Gx <= 0.13) {
											return 0;
										}
										else {
											return 0;
										}
									}
									else {
										if ( AyXGx <= 0.03) {
											if ( AxXGz <= -0.02) {
												return 0;
											}
											else {
												if ( AxXGx <= -0.0) {
													if ( GyXGz <= -0.02) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													if ( AxXGy <= 0.0) {
														return 1;
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( Gx <= -0.12) {
												return 1;
											}
											else {
												return 1;
											}
										}
									}
								}
								else {
									if ( Gx_squared <= -0.14) {
										if ( Gz_squared <= -0.14) {
											if ( AxXAy <= -0.34) {
												return 0;
											}
											else {
												return 0;
											}
										}
										else {
											if ( GxXGy <= 0.01) {
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
									}
									else {
										if ( AyXGz <= 0.2) {
											if ( AxXGz <= -0.02) {
												if ( Gy_squared <= -0.15) {
													if ( AyXAz <= -0.05) {
														if ( AzXGz <= 0.02) {
															return 0;
														}
														else {
															return 1;
														}
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
												else {
													if ( AxXGx <= 0.01) {
														return 1;
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( GxXGy <= 0.02) {
													if ( AxXGx <= 0.01) {
														if ( Gx_squared <= -0.13) {
															if ( Gy_squared <= -0.14) {
																if ( AzXGx <= 0.01) {
																	return 0;
																}
																else {
																	if ( AyXAz <= -0.17) {
																		return 0;
																	}
																	else {
																		if ( AyXGz <= -0.02) {
																			if ( Gz_squared <= -0.13) {
																				return 0;
																			}
																			else {
																				return 0;
																			}
																		}
																		else {
																			if ( AyXGz <= 0.04) {
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
															if ( AxXGy <= 0.04) {
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
											return 0;
										}
									}
								}
							}
						}
						else {
							if ( AxXAy <= -0.07) {
								if ( AxXAz <= -0.19) {
									if ( Ay <= -0.68) {
										if ( GyXGz <= -0.02) {
											return 0;
										}
										else {
											return 0;
										}
									}
									else {
										if ( Gx <= -0.32) {
											return 0;
										}
										else {
											if ( GyXGz <= -0.02) {
												if ( Gy <= -0.01) {
													return 0;
												}
												else {
													if ( GxXGz <= 0.0) {
														return 0;
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( Gy <= 0.24) {
													if ( Ay <= -0.62) {
														if ( AxXGx <= 0.04) {
															return 1;
														}
														else {
															return 1;
														}
													}
													else {
														if ( GxXGz <= 0.0) {
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
								else {
									if ( Ay <= -0.61) {
										if ( AxXAy <= -0.24) {
											if ( Ay <= -0.67) {
												if ( AxXAz <= -0.08) {
													if ( AxXGz <= 0.06) {
														if ( AxXAz <= -0.14) {
															return 0;
														}
														else {
															if ( Gy <= 0.06) {
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
													if ( GxXGy <= 0.01) {
														if ( AzXGy <= -0.03) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														if ( AzXGy <= -0.01) {
															if ( GyXGz <= -0.02) {
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
												if ( AzXGx <= 0.01) {
													if ( Az <= 0.14) {
														return 0;
													}
													else {
														return 1;
													}
												}
												else {
													if ( Gx_squared <= -0.13) {
														if ( Gy_squared <= -0.15) {
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
											if ( AzXGx <= -0.03) {
												return 1;
											}
											else {
												if ( AyXAz <= -0.54) {
													if ( Az_squared <= -0.06) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													if ( Gy_squared <= -0.14) {
														if ( Gy <= 0.17) {
															if ( GyXGz <= -0.02) {
																if ( GyXGz <= -0.03) {
																	if ( GyXGz <= -0.03) {
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
																if ( AxXAz <= -0.0) {
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
														return 1;
													}
												}
											}
										}
									}
									else {
										if ( Gx <= 0.01) {
											return 1;
										}
										else {
											return 0;
										}
									}
								}
							}
							else {
								if ( Gx_squared <= -0.07) {
									if ( AzXGy <= 0.06) {
										if ( AzXGy <= -0.05) {
											if ( Gx_squared <= -0.12) {
												if ( AzXGy <= -0.11) {
													if ( GxXGz <= 0.0) {
														return 0;
													}
													else {
														return 1;
													}
												}
												else {
													if ( Az <= -0.04) {
														if ( Gy_squared <= -0.15) {
															return 0;
														}
														else {
															if ( Gz_squared <= -0.14) {
																return 0;
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( GxXGy <= 0.02) {
															if ( AyXGz <= 0.11) {
																if ( AzXGz <= 0.03) {
																	if ( AzXGz <= 0.01) {
																		if ( Gx <= -0.11) {
																			return 0;
																		}
																		else {
																			return 0;
																		}
																	}
																	else {
																		if ( AyXAz <= 0.23) {
																			return 0;
																		}
																		else {
																			return 0;
																		}
																	}
																}
																else {
																	if ( AzXGz <= 0.04) {
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
															return 1;
														}
													}
												}
											}
											else {
												if ( AyXAz <= 0.41) {
													return 1;
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( AxXGz <= -0.03) {
												if ( Gx <= -0.05) {
													return 0;
												}
												else {
													return 0;
												}
											}
											else {
												if ( Az_squared <= -0.12) {
													if ( AxXAz <= -0.01) {
														if ( Gz <= -0.14) {
															return 1;
														}
														else {
															if ( Az_squared <= -0.17) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AzXGz <= 0.01) {
															if ( AyXGz <= 0.02) {
																if ( AxXGx <= -0.0) {
																	if ( AzXGz <= -0.05) {
																		return 1;
																	}
																	else {
																		if ( GyXGz <= -0.03) {
																			return 0;
																		}
																		else {
																			if ( Gy <= -0.01) {
																				return 1;
																			}
																			else {
																				if ( AzXGx <= 0.02) {
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
																	if ( Gy <= 0.03) {
																		return 0;
																	}
																	else {
																		return 1;
																	}
																}
															}
															else {
																if ( AxXAz <= 0.06) {
																	if ( Gx_squared <= -0.14) {
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
														}
														else {
															if ( AyXGx <= 0.03) {
																if ( Gy_squared <= -0.16) {
																	if ( AyXAz <= -0.46) {
																		return 1;
																	}
																	else {
																		if ( Ay <= -0.71) {
																			return 1;
																		}
																		else {
																			if ( GyXGz <= -0.02) {
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
																		if ( GxXGz <= 0.01) {
																			return 1;
																		}
																		else {
																			return 0;
																		}
																	}
																	else {
																		if ( AxXGy <= 0.0) {
																			return 1;
																		}
																		else {
																			if ( Gz <= -0.15) {
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
																if ( Gy <= 0.11) {
																	if ( AxXGz <= -0.02) {
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
												else {
													if ( AyXGy <= 0.1) {
														if ( Gx <= 0.13) {
															if ( AxXAz <= -0.1) {
																return 0;
															}
															else {
																if ( Gy_squared <= -0.16) {
																	if ( Az <= 2.07) {
																		if ( AyXGz <= 0.03) {
																			if ( Gx <= -0.08) {
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
																	if ( AyXAz <= -0.66) {
																		return 1;
																	}
																	else {
																		if ( AxXGx <= -0.0) {
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
														return 1;
													}
												}
											}
										}
									}
									else {
										if ( AyXAz <= 0.69) {
											if ( GxXGz <= 0.0) {
												return 1;
											}
											else {
												if ( AyXAz <= 0.43) {
													return 1;
												}
												else {
													if ( AxXAy <= 0.19) {
														if ( GxXGz <= 0.01) {
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
					if ( AxXAz <= -0.08) {
						if ( Gy_squared <= -0.15) {
							if ( Ay <= -0.66) {
								return 0;
							}
							else {
								if ( GxXGz <= 0.01) {
									return 1;
								}
								else {
									return 1;
								}
							}
						}
						else {
							if ( GxXGy <= -0.02) {
								return 0;
							}
							else {
								if ( AxXAz <= -0.11) {
									if ( AxXGx <= 0.05) {
										if ( GyXGz <= -0.04) {
											return 0;
										}
										else {
											if ( Ay_squared <= -0.02) {
												return 0;
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( AxXGx <= 0.1) {
											return 0;
										}
										else {
											return 0;
										}
									}
								}
								else {
									if ( AyXGy <= 0.13) {
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
						if ( Az <= -0.62) {
							if ( Az_squared <= 0.15) {
								if ( AxXGx <= -0.01) {
									return 1;
								}
								else {
									if ( Gy_squared <= -0.15) {
										return 0;
									}
									else {
										return 0;
									}
								}
							}
							else {
								if ( AyXGy <= 0.07) {
									return 0;
								}
								else {
									return 0;
								}
							}
						}
						else {
							if ( Ay_squared <= 0.25) {
								if ( GxXGy <= 0.0) {
									if ( AyXAz <= -0.09) {
										if ( Gz <= 0.88) {
											if ( AzXGx <= 0.0) {
												return 1;
											}
											else {
												if ( AxXAz <= 0.07) {
													return 0;
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( AxXAz <= 0.2) {
												if ( AzXGx <= 0.04) {
													return 1;
												}
												else {
													if ( AyXGz <= -0.64) {
														return 1;
													}
													else {
														if ( GxXGy <= -0.0) {
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
										if ( AyXGx <= 0.35) {
											if ( AzXGz <= -0.01) {
												if ( GxXGy <= -0.01) {
													if ( Gz <= 0.37) {
														return 1;
													}
													else {
														return 0;
													}
												}
												else {
													if ( AxXGz <= 0.28) {
														if ( AxXAz <= -0.04) {
															return 1;
														}
														else {
															if ( Az <= -0.15) {
																if ( AzXGz <= -0.18) {
																	return 1;
																}
																else {
																	if ( AxXGz <= -0.01) {
																		if ( AyXGy <= 0.15) {
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
																if ( Gz <= 0.89) {
																	if ( AyXAz <= 0.28) {
																		return 0;
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	if ( Gy_squared <= -0.14) {
																		return 1;
																	}
																	else {
																		if ( GxXGz <= 0.06) {
																			if ( AxXAy <= -0.2) {
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
														if ( AzXGy <= 0.0) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
											}
											else {
												if ( Az <= 0.1) {
													if ( GxXGy <= -0.01) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													if ( AzXGy <= -0.01) {
														return 1;
													}
													else {
														if ( Gy <= -0.21) {
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
											if ( AyXGz <= 0.14) {
												return 1;
											}
											else {
												return 1;
											}
										}
									}
								}
								else {
									if ( AxXGx <= -0.05) {
										if ( AxXAy <= 0.39) {
											if ( Az_squared <= -0.18) {
												if ( AzXGz <= 0.03) {
													if ( AzXGx <= -0.02) {
														return 1;
													}
													else {
														if ( AyXAz <= -0.31) {
															return 1;
														}
														else {
															if ( AyXGz <= 0.15) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( AzXGy <= -0.0) {
														return 1;
													}
													else {
														if ( AyXGz <= 0.16) {
															return 1;
														}
														else {
															if ( GyXGz <= -0.01) {
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
												if ( AzXGx <= -0.08) {
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
										else {
											if ( AyXGx <= -0.23) {
												return 1;
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( AzXGx <= 0.02) {
											if ( AzXGy <= -0.06) {
												if ( Az <= 1.5) {
													if ( AyXGx <= -0.16) {
														if ( AyXAz <= 0.39) {
															if ( GxXGy <= 0.05) {
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
														if ( Gz <= 0.08) {
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
												if ( GxXGy <= 0.04) {
													if ( AxXGy <= 0.02) {
														if ( Az <= 1.03) {
															if ( AxXAz <= -0.03) {
																return 0;
															}
															else {
																if ( AyXAz <= 0.52) {
																	if ( AxXGz <= 0.09) {
																		if ( AyXGx <= -0.12) {
																			if ( Az <= -0.04) {
																				if ( AxXGy <= 0.0) {
																					return 1;
																				}
																				else {
																					if ( AzXGy <= -0.03) {
																						return 0;
																					}
																					else {
																						return 1;
																					}
																				}
																			}
																			else {
																				if ( AxXGz <= 0.0) {
																					if ( GxXGy <= 0.03) {
																						if ( AyXAz <= 0.2) {
																							return 1;
																						}
																						else {
																							if ( AxXGz <= -0.01) {
																								if ( Ay_squared <= 0.03) {
																									return 1;
																								}
																								else {
																									if ( Az_squared <= -0.17) {
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
																				else {
																					return 1;
																				}
																			}
																		}
																		else {
																			if ( AzXGz <= -0.05) {
																				return 1;
																			}
																			else {
																				if ( AyXGz <= -0.09) {
																					if ( AzXGy <= -0.0) {
																						return 1;
																					}
																					else {
																						return 0;
																					}
																				}
																				else {
																					if ( AzXGy <= 0.02) {
																						if ( Ay <= -0.68) {
																							if ( AxXAy <= 0.22) {
																								if ( Gy_squared <= -0.15) {
																									if ( GxXGz <= 0.01) {
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
																						return 1;
																					}
																				}
																			}
																		}
																	}
																	else {
																		if ( AyXGz <= -0.63) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																}
																else {
																	if ( AxXGz <= -0.01) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
															}
														}
														else {
															if ( AxXAz <= 0.08) {
																if ( Az_squared <= -0.22) {
																	return 1;
																}
																else {
																	if ( Gx <= -0.19) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
															}
															else {
																if ( Ay_squared <= -0.02) {
																	return 1;
																}
																else {
																	if ( AyXAz <= -0.48) {
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
														if ( AxXGx <= 0.02) {
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
											if ( AxXGy <= -0.0) {
												if ( AxXGx <= -0.02) {
													return 1;
												}
												else {
													if ( GxXGz <= 0.01) {
														return 0;
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( AyXGx <= 0.14) {
													if ( Az <= -0.01) {
														return 0;
													}
													else {
														if ( AxXGz <= 0.01) {
															if ( AzXGz <= 0.06) {
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
															return 0;
														}
													}
												}
												else {
													if ( AyXAz <= 0.35) {
														if ( AxXAz <= 0.07) {
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
								}
							}
							else {
								if ( Gz_squared <= 0.01) {
									if ( AxXGx <= -0.01) {
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
								else {
									return 1;
								}
							}
						}
					}
				}
			}
			else {
				if ( Gz <= 0.31) {
					if ( AxXAy <= 0.37) {
						if ( GyXGz <= -0.03) {
							if ( AxXAz <= -0.6) {
								if ( AxXAy <= -1.19) {
									return 0;
								}
								else {
									return 0;
								}
							}
							else {
								if ( Ay_squared <= -1.03) {
									return 0;
								}
								else {
									if ( Ay <= -0.45) {
										if ( AyXGx <= 0.14) {
											if ( GyXGz <= -0.03) {
												if ( Gy_squared <= -0.14) {
													if ( GxXGz <= 0.0) {
														if ( AyXGz <= 0.14) {
															return 0;
														}
														else {
															return 1;
														}
													}
													else {
														if ( Ax <= -0.17) {
															return 1;
														}
														else {
															if ( AzXGz <= -0.06) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( AzXGy <= -0.13) {
														if ( Gy_squared <= -0.13) {
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
											}
											else {
												if ( AyXAz <= 0.61) {
													return 1;
												}
												else {
													if ( AzXGx <= 0.08) {
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
										if ( Gy <= -0.23) {
											if ( AyXGx <= -0.01) {
												if ( Gz_squared <= -0.14) {
													return 1;
												}
												else {
													if ( AyXGz <= 0.16) {
														return 1;
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( GxXGy <= 0.0) {
													return 1;
												}
												else {
													if ( AyXGz <= 0.15) {
														if ( Gz <= 0.03) {
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
										else {
											if ( Gx_squared <= -0.08) {
												if ( Az <= 0.82) {
													if ( Az <= -1.51) {
														if ( AxXAz <= -0.08) {
															return 1;
														}
														else {
															return 1;
														}
													}
													else {
														if ( AxXAz <= 0.01) {
															if ( Ay <= -0.32) {
																return 1;
															}
															else {
																return 0;
															}
														}
														else {
															if ( AyXAz <= -0.66) {
																if ( Az <= -0.47) {
																	return 1;
																}
																else {
																	if ( AyXGz <= -0.01) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
															}
															else {
																if ( Ay_squared <= -0.02) {
																	if ( AyXGx <= -0.04) {
																		if ( Gz <= 0.08) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		if ( Gy_squared <= -0.15) {
																			return 0;
																		}
																		else {
																			return 1;
																		}
																	}
																}
																else {
																	if ( AyXGy <= -0.17) {
																		if ( Gx_squared <= -0.13) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		if ( AxXGz <= -0.01) {
																			if ( Ay_squared <= 0.05) {
																				if ( GxXGz <= 0.01) {
																					if ( GxXGz <= 0.01) {
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
							if ( Az <= 0.6) {
								if ( Gx_squared <= -0.1) {
									if ( AyXAz <= -0.72) {
										if ( Az <= -0.51) {
											if ( Az <= -1.76) {
												return 1;
											}
											else {
												if ( Az <= -0.62) {
													if ( AxXAy <= 0.1) {
														return 1;
													}
													else {
														return 0;
													}
												}
												else {
													if ( Gy <= 0.1) {
														if ( AxXGy <= 0.0) {
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
											if ( AxXAy <= 0.22) {
												if ( AxXAz <= 0.11) {
													if ( Ay_squared <= -0.1) {
														return 1;
													}
													else {
														if ( AyXAz <= -0.83) {
															if ( AyXGx <= -0.0) {
																return 1;
															}
															else {
																if ( GyXGz <= -0.02) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( AzXGz <= 0.01) {
																return 1;
															}
															else {
																if ( AxXAy <= 0.1) {
																	return 1;
																}
																else {
																	if ( Gy_squared <= -0.15) {
																		if ( Az_squared <= -0.02) {
																			if ( AyXGz <= -0.04) {
																				return 1;
																			}
																			else {
																				if ( Gx_squared <= -0.14) {
																					if ( Gx_squared <= -0.14) {
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
										if ( AxXGy <= 0.08) {
											if ( AyXGx <= -0.04) {
												if ( AxXAz <= -0.32) {
													if ( Ax_squared <= 0.77) {
														if ( Az <= -0.97) {
															if ( AxXAy <= -0.35) {
																if ( GyXGz <= -0.02) {
																	if ( Gy_squared <= -0.16) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	if ( Ax_squared <= 0.17) {
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
															if ( AzXGz <= 0.1) {
																if ( Gy <= 0.05) {
																	if ( AyXGx <= -0.11) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	if ( Gz <= -0.04) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
															}
															else {
																if ( AyXGy <= 0.12) {
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
													if ( AyXGy <= 0.01) {
														if ( Gx_squared <= -0.13) {
															if ( GxXGy <= 0.01) {
																if ( AyXGz <= 0.03) {
																	if ( Gz <= 0.01) {
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
																if ( AxXAz <= 0.11) {
																	if ( Gz <= -0.1) {
																		if ( AzXGx <= 0.04) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		if ( AzXGy <= -0.0) {
																			if ( Ay <= -0.52) {
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
															if ( Ax_squared <= -0.13) {
																return 1;
															}
															else {
																if ( Az_squared <= 0.12) {
																	if ( Gz_squared <= -0.14) {
																		return 1;
																	}
																	else {
																		return 1;
																	}
																}
																else {
																	if ( AzXGz <= -0.0) {
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
														if ( Gx_squared <= -0.12) {
															if ( Gx <= -0.16) {
																if ( AzXGx <= 0.04) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Ax_squared <= -0.1) {
																	if ( Ax <= -0.56) {
																		return 1;
																	}
																	else {
																		if ( Gz_squared <= -0.14) {
																			return 1;
																		}
																		else {
																			if ( GxXGy <= 0.01) {
																				if ( GxXGz <= -0.0) {
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
																	if ( GyXGz <= -0.02) {
																		if ( AzXGy <= 0.0) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		if ( GxXGz <= -0.01) {
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
											}
											else {
												if ( AzXGy <= -0.01) {
													if ( Gy <= 0.34) {
														if ( Ay_squared <= -0.48) {
															if ( AzXGx <= 0.02) {
																return 1;
															}
															else {
																if ( AxXGy <= 0.01) {
																	if ( AxXGx <= -0.01) {
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
															if ( AxXGy <= 0.01) {
																if ( Az_squared <= 0.36) {
																	if ( Gy <= 0.07) {
																		if ( AyXAz <= -0.27) {
																			if ( Az_squared <= -0.21) {
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
																		if ( AyXAz <= -0.52) {
																			if ( GyXGz <= -0.02) {
																				return 1;
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			if ( AzXGy <= -0.03) {
																				if ( AxXGx <= -0.01) {
																					return 1;
																				}
																				else {
																					return 1;
																				}
																			}
																			else {
																				if ( AyXAz <= -0.28) {
																					if ( Gx <= 0.09) {
																						return 1;
																					}
																					else {
																						return 1;
																					}
																				}
																				else {
																					if ( AxXAz <= -0.12) {
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
																if ( Gz <= -0.17) {
																	return 0;
																}
																else {
																	if ( AyXGx <= -0.02) {
																		return 1;
																	}
																	else {
																		if ( AyXAz <= 0.46) {
																			if ( AxXAy <= 0.23) {
																				return 0;
																			}
																			else {
																				return 1;
																			}
																		}
																		else {
																			if ( AzXGy <= -0.04) {
																				if ( AyXAz <= 0.69) {
																					return 1;
																				}
																				else {
																					if ( Az_squared <= 0.34) {
																						if ( Az_squared <= 0.25) {
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
													else {
														if ( GxXGz <= 0.01) {
															if ( AyXAz <= 0.71) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															if ( AzXGy <= -0.08) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( AxXAz <= -0.67) {
														return 0;
													}
													else {
														if ( AyXGy <= 0.13) {
															if ( AyXAz <= 0.77) {
																if ( AzXGy <= 0.0) {
																	if ( AxXGy <= 0.0) {
																		if ( Ay <= -0.38) {
																			return 0;
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
																	else {
																		if ( AxXGz <= -0.02) {
																			return 0;
																		}
																		else {
																			return 1;
																		}
																	}
																}
																else {
																	if ( Az <= 0.17) {
																		if ( Gx_squared <= -0.14) {
																			return 1;
																		}
																		else {
																			if ( AxXAy <= 0.19) {
																				if ( AyXGy <= 0.06) {
																					if ( AxXGz <= -0.02) {
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
																	else {
																		if ( AyXGx <= 0.04) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																}
															}
															else {
																if ( AxXGy <= -0.02) {
																	return 1;
																}
																else {
																	if ( Az <= -1.4) {
																		return 1;
																	}
																	else {
																		if ( AxXAy <= -0.03) {
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
															return 0;
														}
													}
												}
											}
										}
										else {
											if ( GxXGy <= 0.01) {
												return 0;
											}
											else {
												return 1;
											}
										}
									}
								}
								else {
									if ( Az_squared <= -0.18) {
										if ( AyXGx <= 0.44) {
											return 0;
										}
										else {
											if ( Az_squared <= -0.22) {
												return 1;
											}
											else {
												return 1;
											}
										}
									}
									else {
										if ( Gx_squared <= -0.07) {
											if ( Gz <= -0.13) {
												return 1;
											}
											else {
												return 0;
											}
										}
										else {
											if ( Ay <= 1.29) {
												return 0;
											}
											else {
												if ( Az_squared <= -0.05) {
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
								if ( AxXGx <= 0.07) {
									if ( Ay_squared <= -0.31) {
										if ( AzXGz <= 0.02) {
											return 1;
										}
										else {
											return 0;
										}
									}
									else {
										if ( AyXGy <= 0.17) {
											if ( Gx <= 0.01) {
												if ( GyXGz <= -0.02) {
													if ( AxXGy <= 0.01) {
														return 0;
													}
													else {
														return 1;
													}
												}
												else {
													if ( GxXGz <= 0.01) {
														return 1;
													}
													else {
														if ( Gz_squared <= -0.13) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
											}
											else {
												if ( GxXGz <= 0.01) {
													if ( Gy_squared <= -0.15) {
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
								else {
									return 0;
								}
							}
						}
					}
					else {
						if ( Az_squared <= 0.27) {
							if ( AxXAz <= -0.04) {
								if ( GxXGy <= 0.01) {
									if ( GyXGz <= -0.02) {
										if ( AxXAz <= -0.18) {
											return 0;
										}
										else {
											if ( AxXAy <= 0.5) {
												return 0;
											}
											else {
												if ( AxXGy <= -0.02) {
													return 0;
												}
												else {
													return 0;
												}
											}
										}
									}
									else {
										if ( Gz <= -0.05) {
											return 0;
										}
										else {
											return 0;
										}
									}
								}
								else {
									if ( Ay_squared <= -0.27) {
										return 0;
									}
									else {
										if ( Gx_squared <= -0.02) {
											if ( AyXAz <= -0.77) {
												if ( AxXGx <= -0.02) {
													if ( Gx <= -0.21) {
														if ( AxXAz <= -0.13) {
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
													if ( AxXAy <= 0.63) {
														if ( Gy <= 0.12) {
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
											}
											else {
												if ( AxXGy <= -0.04) {
													if ( Gz_squared <= -0.13) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													if ( Gx_squared <= -0.12) {
														if ( GxXGz <= 0.01) {
															if ( AxXAy <= 0.57) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															if ( AzXGz <= -0.01) {
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
											return 0;
										}
									}
								}
							}
							else {
								if ( Ax <= 0.6) {
									if ( Gx <= -0.02) {
										if ( Gz <= -0.26) {
											return 1;
										}
										else {
											if ( GyXGz <= -0.02) {
												if ( AzXGy <= -0.02) {
													return 1;
												}
												else {
													if ( AzXGy <= 0.03) {
														if ( Gz <= 0.01) {
															return 1;
														}
														else {
															if ( AyXAz <= -0.41) {
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
												if ( AzXGx <= 0.05) {
													if ( Gx_squared <= -0.14) {
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
										if ( AxXGy <= -0.03) {
											if ( Gz_squared <= -0.13) {
												return 0;
											}
											else {
												return 0;
											}
										}
										else {
											if ( AxXGy <= 0.05) {
												if ( Az_squared <= -0.25) {
													return 0;
												}
												else {
													if ( Az_squared <= -0.22) {
														return 1;
													}
													else {
														if ( AzXGz <= 0.0) {
															if ( Gz <= 0.1) {
																return 1;
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
							if ( Gx_squared <= -0.12) {
								if ( AxXAy <= 0.95) {
									if ( Gy <= 0.06) {
										if ( AxXGz <= -0.0) {
											return 1;
										}
										else {
											return 1;
										}
									}
									else {
										if ( Az <= -1.66) {
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
					if ( AyXGz <= 0.51) {
						if ( AxXGz <= 0.07) {
							if ( GyXGz <= -0.05) {
								if ( AzXGx <= 0.02) {
									if ( AyXAz <= -0.35) {
										if ( AzXGy <= 0.03) {
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
									if ( AxXAz <= 0.07) {
										if ( AyXAz <= -0.51) {
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
							}
							else {
								if ( AzXGx <= 0.19) {
									if ( AyXAz <= -0.25) {
										if ( Az <= -0.54) {
											return 0;
										}
										else {
											if ( AxXGy <= 0.02) {
												if ( AxXGz <= -0.01) {
													if ( Az_squared <= -0.07) {
														if ( AxXGz <= -0.05) {
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
													if ( Az <= -0.15) {
														return 0;
													}
													else {
														if ( AxXGy <= -0.01) {
															return 1;
														}
														else {
															if ( AyXGz <= 0.35) {
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
												return 0;
											}
										}
									}
									else {
										if ( AzXGz <= -0.14) {
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
						}
						else {
							if ( AxXAz <= -0.06) {
								if ( GxXGy <= 0.01) {
									if ( AyXAz <= 0.46) {
										return 0;
									}
									else {
										return 0;
									}
								}
								else {
									if ( AxXAy <= -0.1) {
										return 0;
									}
									else {
										if ( Az <= -0.4) {
											return 0;
										}
										else {
											return 0;
										}
									}
								}
							}
							else {
								if ( AyXAz <= -0.49) {
									return 1;
								}
								else {
									if ( Ay_squared <= -0.27) {
										return 0;
									}
									else {
										if ( AyXGx <= 0.03) {
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
						if ( Ay <= 1.41) {
							if ( GxXGz <= -0.0) {
								return 0;
							}
							else {
								return 0;
							}
						}
						else {
							if ( Gx_squared <= -0.06) {
								if ( AyXGx <= 0.11) {
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
	else {
		if ( AyXAz <= -0.64) {
			if ( Gy_squared <= -0.07) {
				if ( Gx_squared <= -0.07) {
					if ( Az <= -0.69) {
						if ( GyXGz <= -0.05) {
							return 0;
						}
						else {
							return 0;
						}
					}
					else {
						if ( Ax_squared <= -0.12) {
							if ( AzXGz <= -0.07) {
								return 0;
							}
							else {
								if ( AzXGx <= 0.08) {
									if ( GxXGy <= 0.02) {
										if ( Az <= -0.37) {
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
						else {
							if ( Gz_squared <= -0.11) {
								if ( Ax <= 0.49) {
									if ( Ay <= -0.52) {
										return 1;
									}
									else {
										if ( Gz_squared <= -0.13) {
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
								if ( Az <= -0.15) {
									if ( AyXGx <= -0.02) {
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
				else {
					if ( Gz_squared <= -0.1) {
						if ( Az <= -0.4) {
							return 0;
						}
						else {
							return 0;
						}
					}
					else {
						if ( GxXGz <= -0.12) {
							return 0;
						}
						else {
							return 0;
						}
					}
				}
			}
			else {
				if ( Az <= 1.57) {
					if ( AyXGy <= -0.48) {
						if ( AzXGy <= 0.38) {
							if ( Gz <= -0.16) {
								if ( Ax_squared <= -0.12) {
									return 0;
								}
								else {
									return 0;
								}
							}
							else {
								if ( Gy <= -0.94) {
									if ( GxXGz <= -0.02) {
										return 0;
									}
									else {
										return 1;
									}
								}
								else {
									if ( GxXGz <= -0.02) {
										return 0;
									}
									else {
										if ( AzXGy <= 0.26) {
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
							if ( Gy_squared <= 2.94) {
								if ( Gz_squared <= -0.02) {
									if ( AzXGz <= 0.0) {
										if ( AxXGz <= -0.02) {
											return 0;
										}
										else {
											if ( AxXAz <= -0.06) {
												return 0;
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( AzXGz <= 0.18) {
											return 0;
										}
										else {
											return 0;
										}
									}
								}
								else {
									if ( Gy <= -2.44) {
										return 0;
									}
									else {
										if ( AyXGz <= 0.54) {
											if ( Gx <= -0.37) {
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
						if ( AxXAz <= 0.02) {
							if ( Gx_squared <= -0.01) {
								if ( Gz_squared <= -0.1) {
									if ( Gy_squared <= -0.03) {
										return 0;
									}
									else {
										return 0;
									}
								}
								else {
									if ( AxXGz <= -0.31) {
										return 0;
									}
									else {
										if ( GyXGz <= -0.11) {
											if ( AzXGy <= -0.38) {
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
								if ( GxXGy <= 0.42) {
									if ( Gz_squared <= 0.06) {
										return 0;
									}
									else {
										return 0;
									}
								}
								else {
									if ( AzXGx <= -0.62) {
										return 0;
									}
									else {
										return 0;
									}
								}
							}
						}
						else {
							if ( AyXGz <= -0.34) {
								return 0;
							}
							else {
								if ( Az_squared <= 0.02) {
									if ( AyXGy <= 0.81) {
										return 0;
									}
									else {
										return 0;
									}
								}
								else {
									if ( AxXGy <= -0.16) {
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
					if ( Ax <= -1.0) {
						return 1;
					}
					else {
						if ( GyXGz <= 0.04) {
							if ( AyXGy <= 0.45) {
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
		else {
			if ( Az <= -0.69) {
				if ( Ay_squared <= -0.12) {
					if ( GyXGz <= 0.05) {
						if ( GyXGz <= -0.25) {
							return 0;
						}
						else {
							if ( Gy_squared <= -0.1) {
								if ( Gz_squared <= -0.1) {
									if ( AzXGy <= -0.25) {
										if ( AxXGy <= 0.08) {
											if ( Ay_squared <= -0.44) {
												return 1;
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
											return 0;
										}
									}
									else {
										if ( GxXGy <= 0.02) {
											if ( Gy <= -0.38) {
												return 0;
											}
											else {
												return 1;
											}
										}
										else {
											if ( Ax <= 0.49) {
												if ( Gz <= -0.29) {
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
									return 1;
								}
							}
							else {
								if ( AxXAz <= -0.47) {
									if ( Gx <= -0.21) {
										return 0;
									}
									else {
										if ( Gy <= 0.93) {
											return 1;
										}
										else {
											return 1;
										}
									}
								}
								else {
									if ( AyXAz <= 0.64) {
										return 0;
									}
									else {
										if ( Gx_squared <= 0.03) {
											if ( GxXGz <= -0.0) {
												if ( Gx <= 0.24) {
													if ( Gy_squared <= -0.06) {
														if ( AzXGx <= 0.2) {
															if ( AyXGx <= 0.1) {
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
														if ( AxXGx <= -0.02) {
															return 1;
														}
														else {
															if ( Az <= -1.08) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( AxXGy <= -0.1) {
														return 1;
													}
													else {
														if ( GyXGz <= -0.08) {
															return 1;
														}
														else {
															if ( AyXGz <= 0.14) {
																return 1;
															}
															else {
																if ( AyXGy <= -0.49) {
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
												if ( AyXGy <= 0.67) {
													if ( AzXGy <= -0.36) {
														if ( AxXGx <= -0.02) {
															return 1;
														}
														else {
															if ( AxXAz <= -0.18) {
																return 1;
															}
															else {
																if ( GxXGz <= 0.0) {
																	return 1;
																}
																else {
																	if ( AyXAz <= 0.85) {
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
														if ( AyXGz <= 0.04) {
															if ( Ay_squared <= -0.31) {
																if ( GxXGz <= 0.03) {
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
												else {
													if ( Az <= -1.19) {
														if ( AyXAz <= 0.86) {
															return 1;
														}
														else {
															return 1;
														}
													}
													else {
														if ( AzXGx <= -0.33) {
															if ( AxXAz <= -0.14) {
																if ( GxXGy <= -0.27) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( GyXGz <= -0.05) {
																	if ( Gx_squared <= -0.02) {
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
											return 1;
										}
									}
								}
							}
						}
					}
					else {
						if ( Ax <= -0.61) {
							if ( Gx_squared <= 0.25) {
								return 1;
							}
							else {
								return 0;
							}
						}
						else {
							if ( Az_squared <= 0.29) {
								return 0;
							}
							else {
								if ( GxXGz <= -0.19) {
									return 0;
								}
								else {
									if ( AxXGz <= 0.1) {
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
					if ( Ay_squared <= 0.19) {
						if ( AyXGy <= -0.35) {
							if ( Gx_squared <= -0.11) {
								return 1;
							}
							else {
								return 0;
							}
						}
						else {
							if ( AzXGy <= 0.95) {
								if ( Gz <= 0.52) {
									if ( Gz_squared <= -0.12) {
										if ( GyXGz <= -0.03) {
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
					else {
						if ( GyXGz <= 0.09) {
							if ( AyXGz <= 0.21) {
								if ( Gx_squared <= 0.19) {
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
							if ( Ax <= -0.89) {
								return 0;
							}
							else {
								if ( AxXGy <= 0.09) {
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
				if ( Ax_squared <= -0.11) {
					if ( AyXGz <= 1.08) {
						if ( Gy_squared <= 0.08) {
							if ( Ay_squared <= -0.24) {
								if ( Ay <= 1.3) {
									if ( Ay_squared <= -0.52) {
										return 0;
									}
									else {
										if ( GxXGz <= 0.02) {
											if ( AyXGz <= 0.13) {
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
								if ( Gz <= -0.26) {
									if ( GyXGz <= -0.3) {
										return 1;
									}
									else {
										if ( Gx <= 1.13) {
											if ( Gz_squared <= -0.12) {
												if ( AyXGy <= 0.42) {
													if ( AxXGz <= -0.02) {
														return 0;
													}
													else {
														if ( AyXGx <= -0.01) {
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
												if ( AxXAz <= 0.04) {
													if ( AzXGz <= 0.16) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													if ( Az <= 0.35) {
														if ( AzXGy <= 0.1) {
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
											if ( Gy_squared <= -0.1) {
												if ( Ax_squared <= -0.13) {
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
									if ( GxXGy <= 0.06) {
										if ( Ay <= -0.76) {
											if ( Gy_squared <= -0.08) {
												if ( Gy <= -0.37) {
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
											if ( GyXGz <= 0.06) {
												if ( Gx <= 0.59) {
													if ( AyXAz <= 0.45) {
														if ( AyXAz <= -0.36) {
															if ( AyXGy <= 0.33) {
																if ( AyXGz <= 0.28) {
																	if ( GxXGy <= 0.02) {
																		if ( AyXGy <= -0.35) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																	else {
																		if ( AxXGz <= -0.02) {
																			return 1;
																		}
																		else {
																			return 1;
																		}
																	}
																}
																else {
																	if ( GyXGz <= -0.14) {
																		if ( AxXGx <= -0.0) {
																			if ( AxXGy <= 0.02) {
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
															else {
																return 0;
															}
														}
														else {
															if ( AyXGz <= -0.61) {
																return 1;
															}
															else {
																if ( AxXGx <= -0.0) {
																	if ( Gx <= 0.04) {
																		if ( AzXGy <= -0.1) {
																			return 0;
																		}
																		else {
																			if ( AyXGy <= 0.3) {
																				if ( AzXGx <= 0.02) {
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
																		if ( AxXGy <= 0.03) {
																			return 0;
																		}
																		else {
																			return 1;
																		}
																	}
																}
																else {
																	if ( AxXAy <= 0.23) {
																		if ( Gz_squared <= -0.12) {
																			if ( AyXAz <= -0.01) {
																				return 1;
																			}
																			else {
																				if ( AxXGz <= -0.01) {
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
																		return 0;
																	}
																}
															}
														}
													}
													else {
														if ( Gz <= 0.09) {
															if ( AxXAz <= 0.05) {
																return 1;
															}
															else {
																if ( AzXGy <= 0.14) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( Gy_squared <= -0.1) {
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
											else {
												if ( Az_squared <= -0.2) {
													if ( AzXGy <= -0.1) {
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
										if ( Gx <= -0.64) {
											if ( AyXGy <= 0.28) {
												return 0;
											}
											else {
												return 0;
											}
										}
										else {
											if ( AyXAz <= -0.38) {
												if ( AyXGy <= -0.53) {
													return 1;
												}
												else {
													if ( Gx <= 0.39) {
														return 0;
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( AzXGy <= 0.07) {
													if ( AyXGx <= -0.39) {
														if ( Gy_squared <= -0.09) {
															return 1;
														}
														else {
															return 0;
														}
													}
													else {
														if ( GyXGz <= -0.01) {
															return 0;
														}
														else {
															if ( GxXGy <= 0.09) {
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
									}
								}
							}
						}
						else {
							if ( Gz <= 0.3) {
								if ( Gx_squared <= -0.05) {
									if ( AyXGy <= -0.77) {
										return 0;
									}
									else {
										if ( Ay <= -0.56) {
											return 0;
										}
										else {
											return 0;
										}
									}
								}
								else {
									if ( AxXGy <= 0.13) {
										if ( GyXGz <= -0.05) {
											return 0;
										}
										else {
											if ( AyXGz <= 0.13) {
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
								if ( Gx <= 0.2) {
									if ( Ay <= 1.34) {
										if ( AyXGz <= -0.56) {
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
									if ( Ax_squared <= -0.13) {
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
						if ( AzXGx <= -0.11) {
							return 0;
						}
						else {
							if ( GxXGy <= 0.04) {
								return 0;
							}
							else {
								if ( Ay_squared <= 0.11) {
									if ( AyXGy <= 1.57) {
										if ( Az_squared <= -0.22) {
											if ( AxXAy <= 0.07) {
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
										if ( AzXGz <= 0.67) {
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
					if ( GyXGz <= 0.02) {
						if ( Gy <= 1.25) {
							if ( Gx <= -0.49) {
								if ( AyXGx <= 0.24) {
									if ( Ay_squared <= -0.27) {
										return 0;
									}
									else {
										if ( AzXGy <= 0.0) {
											return 0;
										}
										else {
											if ( AyXGy <= -0.59) {
												return 0;
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									if ( AxXAy <= -0.44) {
										if ( GxXGy <= -0.07) {
											return 0;
										}
										else {
											if ( Ay <= -0.74) {
												return 0;
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( GyXGz <= -0.04) {
											if ( GxXGz <= -0.07) {
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
							else {
								if ( Gz <= 0.93) {
									if ( Ay_squared <= -0.4) {
										if ( AyXAz <= 0.16) {
											return 0;
										}
										else {
											return 0;
										}
									}
									else {
										if ( AyXGz <= 0.9) {
											if ( Ay <= -0.69) {
												if ( AxXGy <= -0.21) {
													if ( GxXGz <= 0.04) {
														if ( GxXGy <= -0.07) {
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
													if ( AxXGy <= 0.24) {
														if ( Ay_squared <= 0.33) {
															if ( AxXGx <= 0.02) {
																if ( AxXGy <= 0.09) {
																	if ( GxXGz <= 0.01) {
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
																if ( Gy_squared <= -0.08) {
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
												if ( Az_squared <= 0.01) {
													if ( GxXGy <= -0.21) {
														if ( AyXGy <= 0.9) {
															if ( AxXAz <= -0.13) {
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
														if ( Ax <= 0.38) {
															if ( AyXGz <= -0.03) {
																if ( GxXGy <= 0.01) {
																	return 0;
																}
																else {
																	if ( AxXGz <= -0.06) {
																		return 0;
																	}
																	else {
																		return 1;
																	}
																}
															}
															else {
																if ( AxXGy <= -0.07) {
																	if ( Gz <= 0.45) {
																		if ( Gx_squared <= -0.13) {
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
																	if ( Gz <= 0.77) {
																		if ( AxXGz <= -0.08) {
																			return 0;
																		}
																		else {
																			if ( Gy_squared <= -0.06) {
																				if ( AzXGz <= 0.02) {
																					if ( Ax_squared <= -0.09) {
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
																	}
																	else {
																		return 1;
																	}
																}
															}
														}
														else {
															if ( Gz <= -0.45) {
																if ( AxXAy <= -0.45) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gy_squared <= -0.08) {
																	if ( GxXGy <= 0.01) {
																		if ( Gy <= -0.41) {
																			return 0;
																		}
																		else {
																			if ( Gy_squared <= -0.12) {
																				return 0;
																			}
																			else {
																				return 0;
																			}
																		}
																	}
																	else {
																		if ( AyXAz <= 0.44) {
																			if ( Gy <= 0.53) {
																				if ( AyXGx <= 0.08) {
																					if ( GxXGy <= 0.02) {
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
																}
																else {
																	if ( AzXGy <= -0.24) {
																		return 0;
																	}
																	else {
																		if ( AzXGz <= -0.05) {
																			return 0;
																		}
																		else {
																			if ( GxXGz <= 0.01) {
																				if ( AxXGx <= 0.07) {
																					if ( GxXGz <= 0.0) {
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
															}
														}
													}
												}
												else {
													if ( AzXGy <= -0.27) {
														return 1;
													}
													else {
														if ( Gy <= -1.24) {
															return 1;
														}
														else {
															if ( Ay_squared <= -0.17) {
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
								}
								else {
									if ( GxXGy <= -0.03) {
										return 0;
									}
									else {
										if ( AzXGz <= -0.25) {
											return 0;
										}
										else {
											if ( AxXGx <= 0.02) {
												if ( Gy_squared <= -0.11) {
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
							if ( AyXGy <= -0.39) {
								if ( AyXGy <= -1.14) {
									return 0;
								}
								else {
									if ( AxXGx <= 0.07) {
										return 0;
									}
									else {
										return 0;
									}
								}
							}
							else {
								if ( Az <= 0.5) {
									if ( Ay <= 1.46) {
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
						if ( AyXGz <= 1.4) {
							if ( AyXGz <= 0.26) {
								if ( Gz <= 0.52) {
									if ( AzXGy <= 0.36) {
										if ( AxXGz <= 0.18) {
											if ( Gz <= 0.26) {
												if ( AxXGx <= 0.52) {
													if ( AyXGz <= 0.19) {
														if ( AyXGy <= -0.56) {
															if ( AyXGx <= -0.03) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															if ( Gy_squared <= -0.04) {
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
												if ( Gz_squared <= -0.11) {
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
									if ( AxXGy <= 0.41) {
										if ( Gx_squared <= -0.13) {
											return 0;
										}
										else {
											if ( Ay <= -0.88) {
												return 0;
											}
											else {
												if ( AxXGy <= 0.11) {
													return 1;
												}
												else {
													if ( Gx <= -0.73) {
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
										if ( AxXGz <= 0.82) {
											if ( AyXGy <= -1.14) {
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
								if ( AyXGy <= 0.78) {
									if ( Ay_squared <= -0.07) {
										if ( Gx <= -0.02) {
											return 0;
										}
										else {
											if ( Ax <= 0.43) {
												return 0;
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( AxXGz <= -0.14) {
											if ( Gy_squared <= -0.08) {
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
									if ( AzXGy <= 0.41) {
										if ( Gx_squared <= 0.07) {
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
							if ( Gx <= -0.48) {
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