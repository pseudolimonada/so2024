# so2024
Mobile Network Manager project for Operating Systems course




CONFIG:
QUEUE_POS - número de slots nas filas que são utilizadas para armazenar os pedidos de autorizaçãoe os comandos dos utilizadores (>=0)
AUTH_SERVERS_MAX - número máximo de Authorization Engines que podem ser lançados (>=1)
AUTH_PROC_TIME - período (em ms) que o Authorization Engine demora para processar os pedidos
MAX_VIDEO_WAIT - tempo máximo (em ms) que os pedidos de autorização do serviço de vídeo podem aguardar para serem executados (>=1)
MAX_OTHERS_WAIT - tempo máximo (em ms) que os pedidos de autorização dos serviços de música e de redes sociais, bem como os comandos podem aguardar para serem executados (>=1)

Exemplo:
30
6
500
100
300

NOTAS:
a zona de memoria partilhada tem 10kB, existe um exercicio que explica isto, nao é para estar sempre a gerar shared memories. é apra usar aritmetica de ponteiros e structs

