# 🌳 Red-Black Tree Implementation in C

Este repositório contém uma implementação completa e comentada de uma **Árvore Rubro-Negra (Red-Black Tree)** em linguagem C. 
O projeto foi desenvolvido com foco no aprendizado dos princípios de estruturas balanceadas, incluindo inserção, remoção, 
balanceamento automático e tratamento de casos específicos com duplo-preto.

---

## 📚 Sobre

As Árvores Rubro-Negras são árvores binárias de busca auto-balanceadas que garantem complexidade **O(log n)** nas operações de 
inserção, remoção e busca. Essa implementação trata:

- Inserção com balanceamento
- Remoção completa (com suporte a nó duplo-preto)
- Correções baseadas em rotações e recoloração
- Uso de **sentinelas (`ward`)** e **nó duplo-preto (`db`)** para facilitar casos degenerados
- Impressão em pré-ordem com cores

---

## 🛠️ Compilação

Você pode compilar o programa com `gcc`, colando no terminal:

gcc rb.h rb.c main.c -o rb.exe 

---

## 💥Testagem

Podem ser criados arquivos personalizados para testar a implementação.
Crie o arquivo "in.txt" (no VS Code roda apenas com "in" sem formato) e gere as entradas à vontade. Elas podem estar em qualquer 
formato, espaçando as entradas, porem é recomendável ser feito o seguinte:

in:

1 11
1 12
3 12
2
99

out:

[11 - BLACK] 

Onde:
1 X- Inserção de X na árvore.
2- Print de todos os elementos da árvore em percurso pre-order com indicação da cor (texto).
3 X- Remoção de X da árvore.
99- Finaliza o laço, deve estar obrigatoriamente em todas as entradas, do contrario gerará erro.

Como utilizar:

Após o passo anterior de compilar, basta colar no terminal o seguinte:

rb.exe < in > out

Caso não funcione, crie o arquivo out.

Dica: Não precisa redigitar/colar tudo, basta pressionar a tecla para cima (⬆) do teclado no terminal que a instrução anterior
será recuperada.

---

Podem ser adicionados prints ao longo dos desvios para observar seu comportamento. Por exemplo os que estão indicando os casos de hotfix do nó duplo-preto. 
Caso queira ver as remoções, adicione uma saída quando o valor é encontrado (pode servir para observar as aparições da remoção recursiva).

Esse readme foi gerado no Chat GPT e alterado por mim, pois eu estava com a agenda corrida e finalizando os testes na madrugada do dia da 1ª prova da disciplina (AED2).

🧑‍💻 Autor
Cauã de Souza Santos
Estudante de Bacharelado em Ciências da Computação
Desenvolvido como atividade da disciplina Algoritmos e Estruturas de Dados II
