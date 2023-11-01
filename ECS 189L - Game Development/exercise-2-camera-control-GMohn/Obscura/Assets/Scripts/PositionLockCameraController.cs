using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Obscura
{
    public class PositionLockCameraController : AbstractCameraController
    {
        [SerializeField] public Vector3 topLeft;
        [SerializeField] public Vector3 bottomRight;
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

            cameraPosition = new Vector3(targetPosition.x,targetPosition.y,cameraPosition.z);

            this.managedCamera.transform.position = cameraPosition;

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
