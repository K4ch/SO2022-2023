Atualização 2
  . discrepância de códigos de retorno corrigidas (todas as plataformas)
  . adicionada nova versão: linux em Mac/M1 (linux_arm64)
  . versão linux_x64_glibc_2.31 deixa de existir (glibc 2.28 abrange essa)

Atualização 1
  . versões glibc 2.28, 2.31, 2.35 (linux_x64)
  . Mac/Intel e Mac/M1 unificados num único ficheiro "mac"


1) Identificar a versão correta do ficheiro binário (".o") à arquitetura
   usada no projeto (linux intel x64 / Apple/Intel / Apple/M1)
  -> Outra arquitetura? falar com o docente na primeira aula a que for

2) Mudar onome do binário escolhido no ponto anterior para users_lib.o
   (ou seja, apagar os parentesis e o que lá está dentro)

3) Incluir o .h e o binário no projeto

4) Ver o .h para obter mais informações acerca das funções da biblioteca

O ficheiro .c da biblioteca não faz parte do material disponibilizado
