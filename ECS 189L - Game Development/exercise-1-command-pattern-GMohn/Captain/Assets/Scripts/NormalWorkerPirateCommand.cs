using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Captain.Command;

namespace Captain.Command
{
    public class NormalWorkerPirateCommand : ScriptableObject, IPirateCommand
    {
        private float totalWorkDuration;
        private float totalWorkDone;
        private float currentWork;
        private const float PRODUCTION_TIME = 4.0f;
        private bool exhausted = false;

        public NormalWorkerPirateCommand()
        {

        }
        public void OnEnable()
        {
            totalWorkDuration = Random.Range(10,20);
        }


        public bool Execute(GameObject pirate, Object productPrefab)
        {
        
            //This function returns false when no work is done. 
            //After you implement work according to the specification and
            //generate instances of productPrefab, this function should return true.
            //totalWorkDuration = Random.Range(20,40)
            currentWork += Time.deltaTime;
            Debug.Log(currentWork);
            Debug.Log(totalWorkDuration);
            if ((currentWork >= PRODUCTION_TIME) && (exhausted == false)){
                totalWorkDone += currentWork;
                currentWork -= PRODUCTION_TIME;
                Object newItem = Instantiate(productPrefab);


            }
            if (totalWorkDuration > totalWorkDone){
                
                return true;
            }
            
            else {
                totalWorkDuration = 0f;
                exhausted = true;
                return false;
            }
        }
    }
}
