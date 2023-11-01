using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;


namespace Pikmini
{
    public class Publisher : IPublisher
    {

        List<Action<Vector3>> collection = new List<Action<Vector3>>();
    
        public void Unsubscribe(Action<Vector3> notifier)
        {
            collection.Remove(notifier);
        }
        
        public void Subscribe(Action<Vector3> notifier)
        {
            collection.Add(notifier);
        }
        
        public void Notify(Vector3 transform)
        {
            foreach(Action<Vector3> notifier in collection) 
            {
                notifier(transform);
            }
        }
    }
}