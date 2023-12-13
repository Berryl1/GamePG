using UnityEngine;
using UnityEngine.UI;

public class BallController : MonoBehaviour
{
    public float speed = 5f;
    private bool isGameStarted = false;
    public int score = 0; // 점수 변수
    public Text scoreText; // UI Text 요소를 가리키기 위한 변수
    public Text FinalScoreText;
    public GameObject gameOverUI; // GameOver UI 오브젝트
    public GameObject FinishUI;
    public ParticleSystem coinParticleSystem;
    public AudioSource coinSound;
    private bool isPaused = false;
    private bool isZMovementEnabled = true;

    public void SetZMovement(bool enableZMovement)
    {
        isZMovementEnabled = enableZMovement;
    }

        public void SetIsPaused(bool paused)
    {
        isPaused = paused;
    }
    void Update()
    {
        if (!isGameStarted && Input.GetKeyDown(KeyCode.W))
        {
            isGameStarted = true;
        }

        if (isGameStarted && !isPaused && isZMovementEnabled)
        {
            float moveHorizontal = Input.GetAxis("Horizontal");

            Vector3 movement = new Vector3(moveHorizontal, 0f, 1f); // z 축 방향으로 항상 이동하도록 설정
            transform.Translate(movement * speed * Time.deltaTime);
        }
    }

    


    // 충돌 처리
    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Coin"))
        {
            // 충돌한 오브젝트가 "Coin" 태그를 가지고 있다면
            // 점수를 증가시키고, 해당 코인을 제거
            score += 10;

            coinParticleSystem.transform.position = other.transform.position;
            coinParticleSystem.Play();
            coinSound.Play();
            Destroy(other.gameObject);

            // UI Text 요소의 텍스트를 업데이트
            scoreText.text = "Score: " + score.ToString();
        }
        else if (other.CompareTag("ITEM"))
        {
            if (other.name == "2time")
            {
                // 충돌한 오브젝트의 이름이 "2times"라면
                // 점수를 2배로 늘림
                score *= 2;

                // 해당 아이템을 제거할 수 있는 코드 작성
                Destroy(other.gameObject);

                // UI Text 요소의 텍스트를 업데이트
                scoreText.text = "Score: " + score.ToString();
            }
            else if (other.name == "2devide")
            {
                // 충돌한 오브젝트의 이름이 "2devide"라면
                // 점수를 나누기 2
                score /= 2;

                // 해당 아이템을 제거할 수 있는 코드 작성
                Destroy(other.gameObject);

                // UI Text 요소의 텍스트를 업데이트
                scoreText.text = "Score: " + score.ToString();
            }
            else if (other.name == "200minus")
            {
                // 충돌한 오브젝트의 이름이 "200minus"라면
                // 점수를 200 감소시킴
                score -= 200;

                // 해당 아이템을 제거할 수 있는 코드 작성
                Destroy(other.gameObject);

                // UI Text 요소의 텍스트를 업데이트
                scoreText.text = "Score: " + score.ToString();
            }
            else if (other.name == "100plus")
            {
                // 충돌한 오브젝트의 이름이 "100plus"라면
                // 점수를 100 증가시킴
                score += 100;

                // 해당 아이템을 제거할 수 있는 코드 작성
                Destroy(other.gameObject);

                // UI Text 요소의 텍스트를 업데이트
                scoreText.text = "Score: " + score.ToString();
            }

            else if (other.name == "Zero")
            {

                score = 0;

                // 해당 아이템을 제거할 수 있는 코드 작성
                Destroy(other.gameObject);

                // UI Text 요소의 텍스트를 업데이트
                scoreText.text = "Score: " + score.ToString();
            }
        }
        else if (other.CompareTag("Obstrate"))
        {
            if (score < 400)
            {
                // 점수가 400점 미만이면 게임 중지
                isGameStarted = false;

                // GameOver UI를 활성화
                gameOverUI.SetActive(true);
            }
        }

        else if (other.CompareTag("Finish"))
        {
            FinalScoreText.text = "Your Final Score: " + score.ToString();
            isGameStarted = false;

                // GameOver UI를 활성화
                FinishUI.SetActive(true);
        }
    }
    
}
