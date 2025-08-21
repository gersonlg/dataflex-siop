/TITULO_QUADRO RESIDENT

 - Entidade(s) sem arquivo(s) XML referente ao periodo selecionado:
/BODY_QUADRO RESIDENT
    _____________________________________________________________________________________________________________________________________
/*

STRING ST_BODY_QUADRO 255 ST_MESES_QUADRO 255 ST_MES_QUADRO 2 ST_DATA_VALIDADE 10

INTEGER IT_MES_FINAL_QUADRO IT_MES_QUADRO

DATE DT_DATA_VALIDADE DT_DATA_CONFERE

INDICATE TITULO_QUADRO! TRUE

MOVE JN_MES TO IT_MES_FINAL_QUADRO

MOVE ''    TO ST_DATA_VALIDADE
MOVE '01/' TO ST_DATA_VALIDADE

IF JN_MES LT '12' APPEND ST_DATA_VALIDADE (JN_MES + 1) '/' ST_EXERCICIO 
ELSE              APPEND ST_DATA_VALIDADE  '01'        '/' (ST_EXERCICIO + 1)

MOVE ST_DATA_VALIDADE TO DT_DATA_CONFERE

CLEAR ENTIDADE
MOVE ST@EXERCICIO@FINANCEIRO TO ENTIDADE.EXERCICIO 
REPEAT
 FIND GT ENTIDADE BY INDEX.1
 [ FOUND] INDICATE FOUND AS ENTIDADE.EXERCICIO EQ ST@EXERCICIO@FINANCEIRO
 [ FOUND] IF ENTIDADE.ORGAO_TCE NE 0 BEGIN
           INDICATE SOLTA_QUADRO! FALSE
           [~TODAS!] INDICATE SOLTA_QUADRO! AS ENTIDADE.CODIGO EQ JN_COD_ENTIDADE
           [ TODAS!] INDICATE SOLTA_QUADRO! TRUE
           
           IF ((ENTIDADE.DATA_VALIDADE NE '') AND (DT_DATA_CONFERE GT ENTIDADE.DATA_VALIDADE)) BEGIN
            INDICATE SOLTA_QUADRO! FALSE
           END
           
           [ SOLTA_QUADRO!] BEGIN
                              MOVE '' TO ST_MESES_QUADRO
                              MOVE 0  TO IT_MES_QUADRO
                              
                              FOR IT_MES_QUADRO FROM 1 TO IT_MES_FINAL_QUADRO
                               MOVE IT_MES_QUADRO TO ST_MES_QUADRO
                               COMZEROS ST_MES_QUADRO 2

                               CLEAR CONTACOR
                               MOVE ST_EXERCICIO    TO CONTACOR.ANO
                               MOVE ST_MES_QUADRO   TO CONTACOR.MES
                               MOVE ENTIDADE.CODIGO TO CONTACOR.COD_ENTIDADE
                               FIND GT CONTACOR BY INDEX.1
                               [ FOUND] INDICATE FOUND AS CONTACOR.ANO          EQ ST_EXERCICIO
                               [ FOUND] INDICATE FOUND AS CONTACOR.MES          EQ ST_MES_QUADRO
                               [ FOUND] INDICATE FOUND AS CONTACOR.COD_ENTIDADE EQ ENTIDADE.CODIGO
                               [~FOUND] BEGIN
                                         [~TITULO_QUADRO!] BEGIN
                                                             IF ST_MESES_QUADRO NE '' APPEND ST_MESES_QUADRO '-' ST_MES_QUADRO
                                                             ELSE                     APPEND ST_MESES_QUADRO  ST_MES_QUADRO
                                                            END
                                         [ TITULO_QUADRO!] BEGIN
                                                             GOSUB LB_PULA_PAGINA
                                                             OUTPUT TITULO_QUADRO
                                                             INDICATE TITULO_QUADRO! FALSE
                                                             
                                                             MOVE ST_MES_QUADRO TO ST_MESES_QUADRO
                                                            END
                                        END
                              LOOP          
                              
                              [~TITULO_QUADRO!] IF ST_MESES_QUADRO NE '' BEGIN
                                                  GOSUB LB_PULA_PAGINA

                                                  MOVE 'Entidade: ' TO ST_BODY_QUADRO
                                                  APPEND ST_BODY_QUADRO ENTIDADE.CODIGO ' ' ENTIDADE.DESCRICAO ' sem arquivo(s) XML do(s) mes(es): ' ST_MESES_QUADRO
                                                  
                                                  PRINT ST_BODY_QUADRO TO BODY_QUADRO.1
                                                  OUTPUT BODY_QUADRO
                                                 END
                             END
           INDICATE FOUND TRUE
           END
UNTIL [~FOUND]
