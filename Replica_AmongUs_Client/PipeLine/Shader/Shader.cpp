#include "Shader.h"

Shader::Shader()
{
	
}


Shader::~Shader()
{
	SAFE_RELEASE(m_vertexShader);
	SAFE_RELEASE(m_pixelShader);
	SAFE_RELEASE(m_inputLayout);
}


void Shader::Render()
{
	//InputLayout�� IA�ܰ迡 �����Ѵ�
	GETDC->IASetInputLayout(m_inputLayout);

	//���̴��� �� �ܰ迡 �����Ѵ�
	GETDC->VSSetShader(m_vertexShader, NULL, 0);
	GETDC->PSSetShader(m_pixelShader, NULL, 0);

	
	return;
}


