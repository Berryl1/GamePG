using UnityEngine;
using UnityEngine.UI;

public class Start : MonoBehaviour
{
    public GameObject startUI;
    private float displayTime = 2f;

    void Start2()
    {
        startUI.SetActive(true); // 시작 시 UI를 활성화합니다.
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.W))
        {
            startUI.SetActive(false);
        }
    }
}
