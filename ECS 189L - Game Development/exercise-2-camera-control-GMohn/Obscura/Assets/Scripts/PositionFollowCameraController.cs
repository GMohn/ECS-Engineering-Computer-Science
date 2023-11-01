using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Obscura
{
    public class PositionFollowCameraController : AbstractCameraController
    {
        [SerializeField] public float followSpeedFactor;
        [SerializeField] public float leashDistance;
        [SerializeField] public float catchUpSpeed;
        private Camera managedCamera;
        private LineRenderer cameraLineRenderer;

        private void Awake()
        {
            this.managedCamera = this.gameObject.GetComponent<Camera>();
            this.cameraLineRenderer = this.gameObject.GetComponent<LineRenderer>();
        }

        //Use the LateUpdate message to avoid setting the camera's position before
        //GameObject locations are finalized.
        void LateUpdate()
        {
            
            Vector3 targetPosition = this.target.transform.position;
            var playerSpeed = this.target.GetComponent<PlayerController>().GetCurrentSpeed();
            var cameraPosition = this.managedCamera.transform.position;

            cameraPosition = new Vector3(targetPosition.x,targetPosition.y,cameraPosition.z);
            Vector3 endPosition = new Vector3((targetPosition.x-cameraPosition.x),(targetPosition.y-cameraPosition.y),targetPosition.z);

            this.managedCamera.transform.position = Vector3.Lerp(cameraPosition,endPosition,playerSpeed*followSpeedFactor*Time.deltaTime);
            if (this.drawLogic)
            {
                this.cameraLineRenderer.enabled = true;
                this.DrawCameraLogic();
            }
            else
            {
                this.cameraLineRenderer.enabled = false;
            }
        }

        public override void DrawCameraLogic()
        {
            this.cameraLineRenderer.positionCount = 5;
            this.cameraLineRenderer.useWorldSpace = false;
            this.cameraLineRenderer.SetPosition(0, new Vector3(5,0,85));
            this.cameraLineRenderer.SetPosition(1, new Vector3(-5,0,85));
            this.cameraLineRenderer.SetPosition(2, new Vector3(0,0,85));
            this.cameraLineRenderer.SetPosition(3, new Vector3(0,5,85));
            this.cameraLineRenderer.SetPosition(4, new Vector3(0,-5,85));
        }
    }
}
