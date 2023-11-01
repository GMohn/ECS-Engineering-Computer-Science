//Jump and speed boost

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Captain.Command;

namespace Captain.Command
{
    public class Skill1 : ScriptableObject, ICaptainCommand
    {
        private float speed = 15.0f;
        private float jumpForce = 10.0f;

        public void Execute(GameObject gameObject)
        {
            var rigidBody = gameObject.GetComponent<Rigidbody2D>();
            rigidBody.velocity = Vector2.up * jumpForce;
            if (rigidBody != null)
            {
                if (gameObject.GetComponent<SpriteRenderer>().flipX == true)
                {
                    rigidBody.velocity = new Vector2(-this.speed, rigidBody.velocity.y);
                }
                else
                {
                        rigidBody.velocity = new Vector2(this.speed, rigidBody.velocity.y);
                }
            }
        }
    }
}