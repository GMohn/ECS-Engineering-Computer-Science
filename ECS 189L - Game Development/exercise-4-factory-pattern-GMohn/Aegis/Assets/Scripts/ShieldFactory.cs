using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Aegis;

public class ShieldFactory : ShieldSpec
{
    [SerializeField]
    private GameObject spawn;

    void Build(ShieldSpec specs)
    {
        Instantiate(this.spawn, this.GameObject.transform.position,Quaternion.identity);
    }
}
