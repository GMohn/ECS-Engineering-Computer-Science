using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Aegis;

public class ShieldController : MonoBehaviour   
{
    [SerializeField] private float capacity = 100.0f;
    [SerializeField] private float rechargeRate = 1.0f;
    [SerializeField] private float rechargeDelay = 1.0f;
    [SerializeField] private EffectTypes type = EffectTypes.Kinetic;
    [SerializeField] private EffectTypes projectileType = EffectTypes.Kinetic;
    [SerializeField] private EffectTypeColors effectTypeColors;
    [SerializeField] private GameObject scrollingText;
    [SerializeField] private GameObject healthBar;
    [SerializeField] private float currentCapacity = 0.0f;
    private HealthBarController healthBarController;
    private float timer = 0.0f;
    private bool delayStop = false;

    void Awake()
    {
        this.currentCapacity = this.capacity;   

        if (!this.healthBar.TryGetComponent<HealthBarController>(out this.healthBarController))
        {
            Debug.Log("ShieldController expects a health bar.");
        }

        this.healthBarController.ChangeValue(this.currentCapacity / this.capacity);

        this.gameObject.GetComponent<Renderer>().material.SetColor("_Color", this.effectTypeColors.GetColorByEffectType(this.type));     
    }

    private void TakeDamage(float damage)
    {
        float oldCapacity = this.currentCapacity;
        this.currentCapacity -= damage;
        
        if (this.currentCapacity < 0.0f)
        {
            this.currentCapacity = 0.0f;
        }
        if (this.currentCapacity <= 0.0f && oldCapacity > 0)
        {
            FindObjectOfType<SoundManager>().PlaySoundEffect("Explode");
        }
        else if (this.currentCapacity > 0)
        {
            FindObjectOfType<SoundManager>().PlaySoundEffect("Shrink");
        }

        this.healthBarController.ChangeValue(this.currentCapacity / this.capacity);
        
        if(this.scrollingText)
        {
            this.ShowScrollingText(damage.ToString());
        }
    }

    private void ShowScrollingText(string message)
    {
        var scrollingText = Instantiate(this.scrollingText, this.transform.position, Quaternion.identity);
        scrollingText.GetComponent<TextMesh>().text = message;
    }

    private void OnTriggerEnter(Collider other)
    {
        if ("Projectile" == other.tag)
        {
            this.projectileType = other.GetComponent<ProjectileController>().GetEffectType();
            Debug.Log(projectileType);
            Debug.Log(type);
            var damage = other.GetComponent<ProjectileController>().GetDamage();
            //Get damage by projectile type
            switch (this.projectileType) 
            {
                //Projectile is Kinetic
                case EffectTypes.Kinetic:
                    switch (type) 
                    {   
                        //Shield is Kinetic
                        case EffectTypes.Kinetic:
                            TakeDamage(damage);
                            break;
                        
                        //Shield is Energy
                        case EffectTypes.Energy:
                            TakeDamage(damage*.5f);
                            break;
                        
                        //Shield is Arcane
                        case EffectTypes.Arcane:
                            TakeDamage(damage*2);
                            break;
                    }
                    break;

                //Projectile is Energy
                case EffectTypes.Energy:
                    //Shield type
                    switch (type) 
                    {   
                        //Shield is Kinetic
                        case EffectTypes.Kinetic:
                            TakeDamage(damage*2.0f);
                            break;
                        
                        //Shield is Energy
                        case EffectTypes.Energy:
                            TakeDamage(damage);
                            break;
                        
                        //Shield is Arcane
                        case EffectTypes.Arcane:
                            TakeDamage(damage*.5f);
                            break;
                    }
                    break;
                //Projectile is Arcane
                case EffectTypes.Arcane:
                    //Shield type
                    switch (type) 
                    {   
                        //Shield is Kinetic
                        case EffectTypes.Kinetic:
                            TakeDamage(damage*.5f);
                            break;
                        
                        //Shield is Energy
                        case EffectTypes.Energy:
                            TakeDamage(damage*2.0f);
                            break;
                        
                        //Shield is Arcane
                        case EffectTypes.Arcane:
                            TakeDamage(damage);

                            break;
                    }
                    break;
            }
        }

    }

    // Update is called once per frame
    void Update()
    {
        //count time
        timer += Time.deltaTime; 
        var capacityRatio = this.currentCapacity / this.capacity;
        Debug.Log(capacityRatio);
        Debug.Log(this.currentCapacity);
        // if delay has been met
        if (delayStop)
        {
            //add capacity for each frame
            this.currentCapacity += rechargeRate * (1.0f/60.0f);
            //if the capacity is full
            if (capacityRatio >= 1)
            {
                //reset time
                timer = 0.0f;
            }
        }
        //if shield is below max
        if (capacityRatio < 1) 
        {
            //if the timer meets the recharge delay
            if ((timer >= this.rechargeDelay) && delayStop == false)
            {
                //stop delay
                delayStop = true;
            }
            else
            {
                //continue delay
                delayStop = false;
            }
        }
        this.transform.localScale = new Vector3(capacityRatio, capacityRatio, capacityRatio);
        this.gameObject.GetComponent<Renderer>().material.SetColor("_Color", this.effectTypeColors.GetColorByEffectType(this.type));     
    }
}
