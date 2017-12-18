using System.Collections;
using UnityEngine;
[RequireComponent(typeof(ParticleSystem))]
public class attractor : MonoBehaviour
{
    ParticleSystem ps;
    ParticleSystem.Particle[] m_Particles;
    Vector3 accl = new Vector3(0.1f, 0.1f, 0.1f);
    int numParticlesAlive;

    void Start()
    {
        ps = GetComponent<ParticleSystem>();
        if (!GetComponent<Transform>())
        {
            GetComponent<Transform>();
        }
    }

    void Update()
    {
        m_Particles = new ParticleSystem.Particle[ps.main.maxParticles];
        numParticlesAlive = ps.GetParticles(m_Particles);
        for (int i = 0; i < numParticlesAlive; i++)
        {
            Vector3 temp = m_Particles[i].velocity * 1000;
            m_Particles[i].velocity += temp.normalized * accl.magnitude / 100;
            //m_Particles[i].position = Vector3.LerpUnclamped(m_Particles[i].position, target.position, step);
            //m_Particles[i].velocity -= m_Particles[i].velocity.normalized * accl.magnitude / 100;
            //Debug.Log(m_Particles[1].velocity.magnitude.ToString());
        }
        ps.SetParticles(m_Particles, numParticlesAlive);
    }
}