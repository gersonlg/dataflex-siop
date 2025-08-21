//--
//--utilizado nos relatorios de conferencia de xml e nos balancos
//--
/TITULO_R00CONF RESIDENT

 - Entidade(s) sem arquivo(s) XML referente ao periodo selecionado:
/BODY_R00CONF RESIDENT
    __________________________________________________________________________________________________________________________________
/*

STRING ST_BODY_R00CONF 255 ST_MESES_R00CONF ST_MES_R00CONF 2

INTEGER IT_MES_FINAL_R00CONF IT_MES_R00CONF

INDICATE TITULO_R00CONF! TRUE

MOVE JN_MES_FINAL TO IT_MES_FINAL_R00CONF

CLEAR ENTIDADE
MOVE ST@EXERCICIO@FINANCEIRO TO ENTIDADE.EXERCICIO 
REPEAT
 FIND GT ENTIDADE BY INDEX.1
 [ FOUND] INDICATE FOUND AS ENTIDADE.EXERCICIO EQ ST@EXERCICIO@FINANCEIRO
 [ FOUND] IF ENTIDADE.ORGAO_TCE NE 0 BEGIN
           INDICATE SOLTA_R00CONF! TRUE
           [~TODAS!] INDICATE SOLTA_R00CONF! AS ENTIDADE.CODIGO EQ JN_COD_ENTIDADE
           [ SOLTA_R00CONF!] BEGIN
                              MOVE '' TO ST_MESES_R00CONF
                              MOVE 0  TO IT_MES_R00CONF
                              
                              INDICATE SOLTA_MSG! FALSE
                              
                              FOR IT_MES_R00CONF FROM 1 TO IT_MES_FINAL_R00CONF
                               MOVE IT_MES_R00CONF TO ST_MES_R00CONF
                               COMZEROS ST_MES_R00CONF 2
                               
                               CLEAR BALANCO
                               MOVE ENTIDADE.CODIGO TO BALANCO.COD_ENTIDADE
                               MOVE ST_EXERCICIO    TO BALANCO.ANO
                               MOVE ST_MES_R00CONF  TO BALANCO.MES
                               FIND GT BALANCO BY INDEX.1
                               [ FOUND] INDICATE FOUND AS BALANCO.COD_ENTIDADE EQ ENTIDADE.CODIGO
                               [ FOUND] INDICATE FOUND AS BALANCO.ANO          EQ ST_EXERCICIO
                               [ FOUND] INDICATE FOUND AS BALANCO.MES          EQ ST_MES_R00CONF
                               [~FOUND] BEGIN
                                         INDICATE SOLTA_MSG! TRUE
                                         
                                         [~TITULO_R00CONF!] BEGIN
                                                             IF ST_MESES_R00CONF NE '' APPEND ST_MESES_R00CONF '-' ST_MES_R00CONF
                                                             ELSE                      APPEND ST_MESES_R00CONF  ST_MES_R00CONF
                                                            END
                                         [ TITULO_R00CONF!] BEGIN
                                                             GOSUB LB_PULA_PAGINA
                                                             OUTPUT TITULO_R00CONF
                                                             INDICATE TITULO_R00CONF! FALSE
                                                             
                                                             MOVE ST_MES_R00CONF TO ST_MESES_R00CONF
                                                            END
                                        END
                              LOOP          
                              
                              [ SOLTA_MSG!] BEGIN
                                             [~TITULO_R00CONF!] BEGIN
                                                                 GOSUB LB_PULA_PAGINA
                                                                 
                                                                 MOVE 'Entidade: ' TO ST_BODY_R00CONF
                                                                 APPEND ST_BODY_R00CONF ENTIDADE.CODIGO ' ' ENTIDADE.DESCRICAO ' sem arquivo(s) XML do(s) mes(es): ' ST_MESES_R00CONF
                                                                 
                                                                 PRINT ST_BODY_R00CONF TO BODY_R00CONF.1
                                                                 OUTPUT BODY_R00CONF
                                                                END
                                            END
                             END
           INDICATE FOUND TRUE
           END
UNTIL [~FOUND]
