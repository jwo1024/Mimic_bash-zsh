# Mimic_bash-zsh #

------

minishell by jaeyjeon & jiwolee

[Notion 기록](https://accessible-capricorn-be7.notion.site/minishell-6d36971050ec460b9022cbdae1a1fc4f)

----
## 본격 MINISHELL 만들기

구조 만들기 (파싱, 실행, 빌트인, 시그널)
컴파일러 구조 참고 [LINK](https://crystalcube.co.kr/107)

**→ tokenizer** : 문자열을 의미있는 토큰으로 변환한다.

**→ parser** : 토큰을 구조를 가진 구문트리(syntax tree)로 변환한다.
  * here-documantaion `<<`

**→ executor** : 구문 트리에 맞게 실행한다.
  * redirection 
  * pipe 생성 및 fork 자식프로세스 생성 
  * cmd 실행 execve();

**→ built-in** 
  * `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

**→ 시그널**
  * `ctrl + c`, `ctrl + \`, `ctrl + d`

**→ [에러](https://www.notion.so/Shell-ea82c5ace4ac41819fc12ac31265b0ca?pvs=21)**


-----

## 토큰 연결리스트 (tokenizer)

metacharacter(`space`, `tab`, `newline`, `|`, `<`, `>`)를 기준으로 T_WORD, T_REDIR, T_PIPE 세가지 타입으로 구분하여 연결리스트를 생성한다.

* T_PIPE : 파이프 `|`
* T_REDIR : 리다이렉션 `>`,`>>`,`<`,`<<`
* T_WORD : 문자열

<center> <img src="https://www.notion.so/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F458c2e00-a334-4f4e-879c-fb94fedc4d6e%2FUntitled.png?table=block&id=b5f0e31f-cc2f-48eb-9a57-0142c1a180f8&spaceId=f0ee7f21-b5b3-40e9-9c73-bd03c03b3423&width=2000&userId=f6d84edb-02b2-4a9f-a07d-406a135703b6&cache=v2" width="80% height="80%"> </center>

## **Syntax Tree (parser)**

토큰 연결리스트를 구문트리로 변환한다.
* T_PIPE : 파이프
* T_CMD  : T_CMD 노드는 하나의 프로세스 실행 단위가 된다. 
* T_REDIR : 리다이렉션 정보가 담겨있다. 리다이렉션은 여러개 존재할 수 있으며 왼쪽노드로 연결리스트 형태로 연결된다. 
* T_SIMP_CMD :  실행할 명령어와 인자, 옵션이 담겨있다.

#### syntax_tree
<center> <img alt="syntax_tree" src="https://www.notion.so/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2Fc56d0a58-9449-4d42-8f99-b040b6673570%2FUntitled.png?table=block&id=73287518-ddff-45d7-8c3c-facacfa2125c&spaceId=f0ee7f21-b5b3-40e9-9c73-bd03c03b3423&width=2000&userId=f6d84edb-02b2-4a9f-a07d-406a135703b6&cache=v2" width="80% height="80%"> </center>

#### syntax_tree 단순화 모형    
<center> <img alt="syntax_tree 단순화 모형" src="https://www.notion.so/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2Fdfc96364-7718-4b4e-8e78-5c338569482b%2FUntitled.png?table=block&id=afb15c70-f129-4186-8dd1-b80ecc5754aa&spaceId=f0ee7f21-b5b3-40e9-9c73-bd03c03b3423&width=2000&userId=f6d84edb-02b2-4a9f-a07d-406a135703b6&cache=v2" width="80% height="80%"> </center>

## Syntax 문법 .bnf
(배커스-나우르 표기법, Backus–Naur form)
Minishell의 syntax 문법의 기준
    
```
    
    <pipeline>     ::= <cmd>
                   |   <pipeline> '|' <cmd>
    
    <cmd>          ::= <simple_cmd>
                   |   <simple_cmd> <redirects>
                   |   <redirects> <simple_cmd> <redirects>
                   |   <simple_cmd> <redirects> <args>
    
    <simple_cmd>   ::= <file_path>
                   |   <file_path> <args>
    
    <redirects>    ::= <io_redirect>
                    |  <redirects> <io_redirect>
    
    <io_redirect>  ::= '<'   <filename>
                    |  '<<'  <filename>
                    |  '>'   <filename>
                    |  '>>'  <filename>
    
    <args>        ::= WORD
                    | <args> WORD
    
    <filename>    ::= WORD
    
    <file_path>   ::= WORD
```
    
출처 : https://epicarts.tistory.com/163 에서 약간의 수정
https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#tag_02_10_02
