using System.Net.Mime;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MainMenu : MonoBehaviour
{
    public GameObject StartCanvus;
    public GameObject HowToPlay;
    public GameObject Option;
    public AudioSource backgroundMusic;
    public Slider volumeSlider; // Inspector에서 MainMenuCanvas에 있는 Slider를 할당해주세요

    // Start is called before the first frame update
    void Start()
    {
        if (backgroundMusic != null)
        {
            backgroundMusic.Play();
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void OnClickNewGame()
    {
        GameObject mainMenu = GameObject.Find("MainMenuCanvas");
        if (mainMenu != null)
        {
            mainMenu.SetActive(false);
        }

        if (StartCanvus != null)
        {
            StartCanvus.SetActive(true);
        }
            
    }

    public void OnClickHowToPlay()
    {
        if (HowToPlay != null)
        {
            HowToPlay.SetActive(true);
        }
    }

    public void OnclickOption()
    {
        if (Option != null)
        {
            Option.SetActive(true);
        }
    }

    public void OnClickQuit()
    {
#if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
#else
        Application.Quit();
#endif
    }

    public void OnVolumeChanged()
    {
        if (backgroundMusic != null && volumeSlider != null)
        {
            backgroundMusic.volume = volumeSlider.value;
        }
    }

    public void OnClickClose()
    {
        if (HowToPlay != null)
        {
            HowToPlay.SetActive(false);
            Option.SetActive(false);
        }
        
    }
}
