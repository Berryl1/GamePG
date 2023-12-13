using UnityEngine;
using UnityEngine.UI;

public class PauseController : MonoBehaviour
{
    public Text pauseText; // 일시정지 시 표시할 텍스트
    private bool isPaused = false; // 게임이 일시정지되었는지 여부를 나타내는 변수

    public void OnPauseButtonClicked()
    {
        if (isPaused)
        {
            // 이미 일시정지된 상태에서 Pause 버튼을 다시 누르면
            // 텍스트를 비활성화하고 게임 일시정지를 해제
            pauseText.gameObject.SetActive(false);
            Time.timeScale = 1f; // 게임 시간 비율을 원래대로 복구
            isPaused = false;
        }
        else
        {
            // 일시정지되지 않은 상태에서 Pause 버튼을 누르면
            // 텍스트를 활성화하고 게임을 일시정지
            pauseText.gameObject.SetActive(true);
            Time.timeScale = 0f; // 게임 시간 비율을 0으로 설정하여 일시정지
            isPaused = true;
        }

        BallController ballController = FindObjectOfType<BallController>();
        if (ballController != null)
        {
            ballController.SetIsPaused(isPaused);
            ballController.SetZMovement(!isPaused); // isPaused 값의 반대로 z축 이동 설정
        }
    }
}
