using UnityEngine;

public class CameraController : MonoBehaviour
{
    public Transform target;
    public Vector3 offset = new Vector3(0f, 3f, -10f);
    public Vector3 rotation = new Vector3(10f, 0f, 0f); // 카메라의 회전 값

    void LateUpdate()
    {
        if (target != null)
        {
            Vector3 desiredPosition = target.position + offset;
            transform.position = desiredPosition;

            Quaternion targetRotation = Quaternion.Euler(rotation); // 카메라의 회전 값을 쿼터니언으로 변환
            transform.rotation = targetRotation;

            transform.LookAt(target);
        }
    }
}
