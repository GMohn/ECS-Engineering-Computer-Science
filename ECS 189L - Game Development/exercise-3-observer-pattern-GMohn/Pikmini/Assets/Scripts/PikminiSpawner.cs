using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class PikminiSpawner : MonoBehaviour
{
    [SerializeField]
    private GameObject spawn;
    
    void Update ()
    {
        if (Input.GetButton("Fire2"))
        {
            Instantiate(this.spawn, this.gameObject.transform.position, Quaternion.identity);
            FindObjectOfType<SoundManager>().PlaySoundEffect("NewMini");
        }
        
    }
}
