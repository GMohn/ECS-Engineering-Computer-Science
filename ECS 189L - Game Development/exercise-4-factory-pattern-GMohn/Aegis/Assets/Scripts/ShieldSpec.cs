using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Aegis;

    public class ShieldSpec : MonoBehaviour
    {
        [SerializeField] private float capacity;
        [SerializeField] private float rechargeDelay;
        [SerializeField] private float rechargeRate;
        [SerializeField] private EffectTypes type;
    }
