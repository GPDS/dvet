# dvet
Digital Video Evaluation Tool

Esse sistema consiste em uma interface gráfica para automatizar a execução de diversos algoritmos de processamento de vídeo digital. O usuário terá acesso a uma vasta base de vídeos YUV de referência. Esses vídeos serão submetidos a todos os algoritmos disponíveis no sistema e todas as informações resultantes relacionadas a cada vídeo serão armazenadas em um banco de dados. Serão implementadas diversas métricas de avaliação de qualidade de vídeo digital, diferentes algoritmos de transcodificação e técnicas de transformação. O framework de algortimos deve ser implementado de forma modular para suportar a adição de novos algoritmos a qualquer momento. 

Uma das principais virtudes desse sistema será a automatização da execução de várias atividades em série e a confecção de um detalhado relatório para facilitar a posterior analise da sequência de simulações propostas. 

O framework deve ser disponibilizado como um DSO (Dinamic Shared Object) que será ligado (linked) à interface gráfica desenvolvida. O objetivo dessa forma de artefato é poder usar os métodos disponibilizados nele dentro de um codificador de vídeo qualquer como forma de estudar relações entre esses algoritmos e o processo de codificação de codificadores escritos em C++. 

Esse projeto visa desenvolver uma ferramenta de referência para o ambiente acadêmico e disponibilizar-la sob licenças de código livre para a comunidade.
