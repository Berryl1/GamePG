using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectRotator : MonoBehaviour
{
    public bool isRotating = true; // 회전 상태를 나타내는 변수
    public float rotationSpeed = 50f; // 회전 속도

    public bool rotateAroundX = true; // x축 회전 여부
    public bool rotateAroundY = true; // y축 회전 여부
    public bool rotateAroundZ = true; // z축 회전 여부

    // Update is called once per frame
    void Update()
    {
        if (isRotating)
        {
            // 회전 축을 선택하여 오브젝트를 회전시킴
            Vector3 rotationAxis = new Vector3(rotateAroundX ? 1f : 0f, rotateAroundY ? 1f : 0f, rotateAroundZ ? 1f : 0f);
            transform.Rotate(rotationAxis * rotationSpeed * Time.deltaTime);
        }
    }
}
