import sys
'''
This function creates a prediction by getting the sum of the list items multipled by weights
Then check if the summation exceeds the given threshold. if yes, predict true else false
'''  
def prediction(inputs, weights,threshold):
    summation = 0
    inputWeight = zip(inputs,weights)
    for i,w in inputWeight:
        summation += i*w
    if summation > threshold:
        return True
    return False
'''
This function gets data, creates a prediction based on current weights
Then makes an adjustment to the weights based on whether the prediction was correct or not. 
'''
def perceptron(threshold, adjustmentfactor, initialweights, examples, numpasses):
    dictSolution = {'init': {'weights': initialweights, 'threshold': threshold, 'adjustment': adjustmentfactor}}
    #print(dictSolution)
    newWeights = initialweights.copy()
    for i in range(numpasses):
        #reset list of training for each pass
        listSol =[]
        #print("Pass ", i+1,"\n")
        #iterates through each example

        for j in range(len(examples)):
            #calculate prediction
            predict = prediction(examples[j][1],newWeights,threshold)
            #print("inputs: ", examples[j][1])
            #print("prediction: ",predict,"\t answer: ",examples[j][0])
            
            #for loop to change each weight value            
            for k in range(len(newWeights)):
                exampleVal = examples[j][1][k]
                
                #positive example and prediction is wrong
                if not predict and examples[j][0]:
                    
                    #increment weight
                    newWeights[k] = newWeights[k]+(adjustmentfactor*exampleVal)
                
                #negative example and prediction is wrong
                elif predict and not examples[j][0]:
                    
                    #decrement weight
                    newWeights[k] = newWeights[k]+(-adjustmentfactor*exampleVal)
                
                #prediction must be correct, no changes need to be made
                else:
                    continue            
            #print("adjusted weights: ",initialweights)
            
            #create dictionary of currently trained process and append to a list
            currentDictionary = {'inputs':examples[j][1], 'prediction':predict,'answer':examples[j][0],'adjusted_weights':newWeights.copy()}
            listSol.append(currentDictionary)
        
        #assign list to key of pass number    
        dictSolution[i+1] = listSol
        
           
    return dictSolution








perceptron(.4,.09,[.3,-.6],[
            [True, [1, 1]],
            [False, [0, 0]],
            [True, [0, 1]],
            [True, [1, 0]]
        ],2)
'''perceptron(.5,.1,[-0.5, 0, 0.5, 0, -0.5],[[True,  [1,1,1,1,0]], 
                                        [False, [1,1,1,1,1]], 
                                        [False, [0,0,0,0,0]], 
                                        [False, [0,0,1,1,0]], 
                                        [False, [1,0,1,0,1]], 
                                        [False, [1,0,1,0,0]], 
                                        [False, [0,1,0,1,1]], 
                                        [False, [0,1,0,1,0]], 
                                        [False, [0,0,1,0,0]], 
                                        [False, [0,0,0,1,0]]], 4)'''