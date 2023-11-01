using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Obscura
{
    public class FrameAutoScrollCameraController : AbstractCameraController
    {
        [SerializeField] public Vector3 topLeft;
        [SerializeField] public Vector3 bottomRight;

        [SerializeField] private float autoScrollSpeed = 20.0f;
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
            var targetPosition = this.target.transform.position;
            var cameraPosition = this.managedCamera.transform.position;

            if (targetPosition.y >= cameraPosition.y + topLeft.y)
            {
                targetPosition.y = cameraPosition.y + topLeft.y;
                this.target.transform.position =  new Vector3(targetPosition.x, cameraPosition.y + topLeft.y, targetPosition.z); 
            }

            if (targetPosition.y <= cameraPosition.y + bottomRight.y)
            {
                targetPosition.y = bottomRight.y;
                this.target.transform.position =  new Vector3(targetPosition.x, cameraPosition.y+bottomRight.y, targetPosition.z); 
            }

            if (targetPosition.x >= cameraPosition.x + bottomRight.x)
            {
                targetPosition.x = cameraPosition.x + bottomRight.x;
                this.target.transform.position =  new Vector3(cameraPosition.x+ bottomRight.x, targetPosition.y, targetPosition.z); 
            }
            
            if (targetPosition.x <= cameraPosition.x + topLeft.x)
            {
                targetPosition.x = topLeft.x;
                this.target.transform.position =  new Vector3(cameraPosition.x+topLeft.x, targetPosition.y, targetPosition.z); 
                               
            }

            this.managedCamera.transform.position += (Vector3.right * autoScrollSpeed * Time.deltaTime);       
            

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
            this.cameraLineRenderer.SetPosition(0, topLeft);
            this.cameraLineRenderer.SetPosition(1, new Vector3(bottomRight.x, topLeft.y, topLeft.z));
            this.cameraLineRenderer.SetPosition(2, bottomRight);
            this.cameraLineRenderer.SetPosition(3, new Vector3(topLeft.x, bottomRight.y, bottomRight.z));
            this.cameraLineRenderer.SetPosition(4, topLeft);
        }
    }
}
