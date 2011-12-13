PHP_FUNCTION(pcsc_test)
{

  //php_printf("Huhudeldiehu: %d::\n", hContext);
    
  char *strReaders = "";
  char *ptrReader;
  DWORD dwLen = SCARD_AUTOALLOCATE;
  LONG rc3;
  
  /*
  LONG rc;
  rc = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &hContext);
  if (rc != SCARD_S_SUCCESS)
  {
    lLastError = rc;
    return FAILURE;
  }
  */
  
  
  
  
/*  php_printf("%d: %d<br/>\n", __LINE__, SCARD_S_SUCCESS);
  php_printf("%d: %d<br/>\n", __LINE__, lLastError);
  php_printf("%d: %d<br/>\n", __LINE__, hContext);
  rc3 = SCardListReaders(hContext, NULL, (char *) &strReaders, &dwLen);
  php_printf("%d: %d<br/>\n", __LINE__, hContext);
  php_printf("%d: %d<br/>\n", __LINE__, lLastError);
*/
  
  if (rc3 != SCARD_S_SUCCESS)
  {
    php_printf("%d: %d<br/>\n", __LINE__, 1);
    lLastError = rc3;
    php_printf("%d: %d<br/>\n", __LINE__, rc3);
    //RETURN_FALSE;
  }

  if (strReaders == NULL) {
    php_printf("%d: %d<br/>\n", __LINE__, 2);
    //RETURN_FALSE;
  }
  
  array_init(return_value);

  ptrReader = strReaders;
  do
  {
    add_next_index_string(return_value, ptrReader, TRUE);
    ptrReader += strlen(ptrReader); /* End of the line */
    ptrReader ++;             /* Beginning of next list */
  } while (*ptrReader != '\0');
  
  SCardFreeMemory(hContext, strReaders);
    


}


/* {{{ proto long scardconnect(string reader_name, [long preferred_protocol], [long &current_protocol])
   Return a handle to the card */
PHP_FUNCTION(scardconnect)
{
  DWORD dwPreferredProtocol, dwCurrentProtocol;
  SCARDHANDLE hCard;
  char *strReader;
  LONG rc;
  PARSE_ARGS(1, 3);

  hLastCard = 0;

  if (ARG(0)->type == IS_LONG)
  {
    /* Find reader by index */
    char *strReaders = NULL;
    char *ptrReader;
    LONG idxReader;
    DWORD dwLen = SCARD_AUTOALLOCATE;

    /* Reader name not supplied, select it in readers list */
    rc = SCardListReaders(hContext, NULL, (char *) &strReaders, &dwLen);
    if (rc != SCARD_S_SUCCESS)
    {
      lLastError = rc;
      RETURN_FALSE;
    }

    if (strReaders == NULL)
      RETURN_FALSE;

    /* Loop */
    idxReader = 0;
    ptrReader = strReaders;
    do
    {
      if (idxReader == ARG(0)->value.lval)
      {
        strReader = estrdup(ptrReader);
        break;
      }
      idxReader ++;
      ptrReader += strlen(ptrReader); /* End of the line */
      ptrReader ++;             /* Beginning of next list */
    } while (*ptrReader != '\0');

    SCardFreeMemory(hContext, strReaders);

    /* Check */
    if (strReader == NULL)
      RETURN_FALSE; /* Reader not found ? */
  } else
  {
    /* Use reader's name */
    strReader = estrdup(ARG(0)->value.str.val);
  }

  /* Preferred protocol */
  if (argc >= 2)
  {
    convert_to_long(ARG(1));
    dwPreferredProtocol = ARG(1)->value.lval;
  } else
  {
    /* dwPreferredProtocol = SCARD_PROTOCOL_DEFAULT | SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1; */
    dwPreferredProtocol = SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1;
  }

  /* Perform the function */
  rc = SCardConnect(hContext, strReader, SCARD_SHARE_SHARED, dwPreferredProtocol, &hCard, &dwCurrentProtocol);

  /* Free the string ASAP */
  efree(strReader);

  if (rc != SCARD_S_SUCCESS)
  {
    lLastError = rc;
    RETURN_FALSE;
  }

  /* Current protocol */
  if ((argc >= 3) && (PZVAL_IS_REF(ARG(2))))
  {
    ARG(2)->value.lval = dwCurrentProtocol;
    ARG(2)->type = IS_LONG;
  }

  /* We store a copy of the handle in case we need it in a shortcut function */
  hLastCard = hCard;

  /* We return the handle */
  RETURN_LONG(hCard);
}
/* }}} */

/* {{{ proto boolean scardreconnect([long card_handle], [long preferred_protocol], [long initialisation], [long &current_protocol])
   Return a handle to the card */
PHP_FUNCTION(scardreconnect)
{
  DWORD dwPreferredProtocol, dwInitialization, dwCurrentProtocol;
  SCARDHANDLE hCard;
  LONG rc;
  PARSE_ARGS(0, 4);

  hLastCard = 0;

  if (argc >= 1)
  {
    convert_to_long(ARG(0));
    hCard = ARG(0)->value.lval;
  } else
  {
    hCard = hLastCard;
  }

  /* Preferred protocol */
  if (ARG(1) != NULL)
  {
    convert_to_long(ARG(1));
    dwPreferredProtocol = ARG(1)->value.lval;
  } else
  {
    /*
    dwPreferredProtocol = SCARD_PROTOCOL_DEFAULT | SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1;
    */
    dwPreferredProtocol = SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1;
  }

  /* Initialisation */
  if (ARG(2) != NULL)
  {
    convert_to_long(ARG(2));
    dwInitialization = ARG(2)->value.lval;
  } else
  {
    dwInitialization = SCARD_LEAVE_CARD;
  }

  /* Perform the function */
  rc = SCardReconnect(hCard, SCARD_SHARE_SHARED, dwPreferredProtocol, dwInitialization, &dwCurrentProtocol);

  if (rc != SCARD_S_SUCCESS)
  {
    lLastError = rc;
    RETURN_FALSE;
  }

  /* Current protocol */
  if ((ARG(3) != NULL) && (PZVAL_IS_REF(ARG(3))))
  {
    ARG(3)->value.lval = dwCurrentProtocol;
    ARG(3)->type = IS_LONG;
  }

  /* OK */
  RETURN_TRUE;
}
/* }}} */

/* {{{ proto boolean scarddisconnect([long card_handle], [long disposition])
   Close a card connection obtained with scardconnect */
PHP_FUNCTION(scarddisconnect)
{
  SCARDHANDLE hCard;
  DWORD dwDisposition;
  LONG rc;
  PARSE_ARGS(0, 2);

  /* Retrieve parameters */
  hCard         = hLastCard;
  dwDisposition = SCARD_EJECT_CARD;

  if (argc >= 1)
  {
    convert_to_long(ARG(0));
    hLastCard   = ARG(0)->value.lval;
  }

  if (argc >= 2)
  {
    convert_to_long(ARG(1));
    dwDisposition = ARG(1)->value.lval;
  }

  /* Disconnect */
  rc = SCardDisconnect(hCard, dwDisposition);

  if (rc != SCARD_S_SUCCESS)
  {
    lLastError = rc;
    RETURN_FALSE;
  }

  /* Drop current card handle */
  if (hLastCard == hCard)
    hLastCard = 0;

  /* OK */
  RETURN_TRUE;
}
/* }}} */

/* {{{ proto array scardstatus([long card_handle])
   Retrieve reader's or card's status */
PHP_FUNCTION(scardstatus)
{
  SCARDHANDLE hCard = 0;
  char *strReader = NULL;
  DWORD dwProtocol, dwState;
  BYTE atrBuffer[32];
  DWORD atrLen;
  LONG rc;
  PARSE_ARGS(0, 1);

  /* Retrieve parameters */
  if (argc >= 1)
  {
    hCard = ARG(0)->value.lval;
  } else
  {
    hCard = hLastCard;
  }

  /* Read card's status */
  atrLen = sizeof(atrBuffer);
  rc = SCardStatus(hCard, NULL, NULL, &dwState, &dwProtocol, atrBuffer, &atrLen);

  if (rc != SCARD_S_SUCCESS)
  {
    lLastError = rc;
    RETURN_FALSE;
  }

  /* Put result in an array */
  array_init(return_value);

  add_assoc_long(return_value, "state",    dwState);

  if (dwState & SCARD_ABSENT)
    add_assoc_long(return_value, "SCARD_ABSENT", 1);

  if (dwState & SCARD_PRESENT)
    add_assoc_long(return_value, "SCARD_PRESENT", 1);

  if (dwState & SCARD_SWALLOWED)
    add_assoc_long(return_value, "SCARD_SWALLOWED", 1);

  if (dwState & SCARD_POWERED)
    add_assoc_long(return_value, "SCARD_POWERED", 1);

  if (dwState & SCARD_NEGOTIABLE)
    add_assoc_long(return_value, "SCARD_NEGOTIABLE", 1);

  if (dwState & SCARD_SPECIFIC)
    add_assoc_long(return_value, "SCARD_SPECIFIC", 1);

  switch (dwProtocol)
  {
    case SCARD_PROTOCOL_RAW : add_assoc_long(return_value, "SCARD_PROTOCOL_RAW", 1);
                              add_assoc_string(return_value, "protocol", "RAW", TRUE);
                              break;
    case SCARD_PROTOCOL_T0  : add_assoc_long(return_value, "SCARD_PROTOCOL_T0", 1);
                              add_assoc_string(return_value, "protocol", "T=0", TRUE);
                              break;
    case SCARD_PROTOCOL_T1  : add_assoc_long(return_value, "SCARD_PROTOCOL_T1", 1);
                              add_assoc_string(return_value, "protocol", "T=1", TRUE);
                              break;
    default                 : add_assoc_long(return_value, "protocol", dwProtocol);
  }

  if (atrLen)
  {
    char *atrString;
    atrString = e_bytes_to_hex(atrBuffer, atrLen);
    add_assoc_string(return_value, "atr", atrString, TRUE);
    efree(atrString);
  }
}
/* }}} */

/* {{{ proto array scardgetstatuschange(string reader_name, [long current_state])
   Retrieve the status of a reader */
PHP_FUNCTION(scardgetstatuschange)
{
  SCARD_READERSTATE rgReaderState = { 0 };
  LONG rc;
  PARSE_ARGS(1, 2);

  /* Retrieve parameters */
  rgReaderState.szReader = ARG(0)->value.str.val;

  if (argc >= 2)
  {
    convert_to_long(ARG(1));
    rgReaderState.dwCurrentState = ARG(1)->value.lval;
  } else
  {
    rgReaderState.dwCurrentState = SCARD_STATE_UNAWARE;
  }
 
  /* Read reader's status */
  rc = SCardGetStatusChange(hContext, 0, &rgReaderState, 1);
  if (rc != SCARD_S_SUCCESS)
  {
    lLastError = rc;
    RETURN_FALSE;
  }

  /* Put result in an array */
  array_init(return_value);

  add_assoc_long(return_value, "state",    rgReaderState.dwEventState);

  if (rgReaderState.dwEventState & SCARD_STATE_IGNORE)
    add_assoc_long(return_value, "SCARD_STATE_IGNORE", 1);

  if (rgReaderState.dwEventState & SCARD_STATE_UNKNOWN)
    add_assoc_long(return_value, "SCARD_STATE_UNKNOWN", 1);

  if (rgReaderState.dwEventState & SCARD_STATE_UNAVAILABLE)
    add_assoc_long(return_value, "SCARD_STATE_UNAVAILABLE", 1);

  if (rgReaderState.dwEventState & SCARD_STATE_EMPTY)
    add_assoc_long(return_value, "SCARD_STATE_EMPTY", 1);

  if (rgReaderState.dwEventState & SCARD_STATE_PRESENT)
    add_assoc_long(return_value, "SCARD_STATE_PRESENT", 1);

  if (rgReaderState.dwEventState & SCARD_STATE_ATRMATCH)
    add_assoc_long(return_value, "SCARD_STATE_ATRMATCH", 1);

  if (rgReaderState.dwEventState & SCARD_STATE_EXCLUSIVE)
    add_assoc_long(return_value, "SCARD_STATE_EXCLUSIVE", 1);

  if (rgReaderState.dwEventState & SCARD_STATE_INUSE)
    add_assoc_long(return_value, "SCARD_STATE_INUSE", 1);

  if (rgReaderState.dwEventState & SCARD_STATE_MUTE)
    add_assoc_long(return_value, "SCARD_STATE_MUTE", 1);

  if (rgReaderState.cbAtr)
  {
    char *atrString;
    atrString = e_bytes_to_hex(rgReaderState.rgbAtr, rgReaderState.cbAtr);
    add_assoc_string(return_value, "atr", atrString, TRUE);
    efree(atrString);
  }
}
/* }}} */


/* {{{ proto string scardtransmit([long card_handle], string send_command)
   Transmit (and receive) data to (and from) the card */
PHP_FUNCTION(scardtransmit)
{
  SCARDHANDLE hCard;
  DWORD dwProtocol, dwState;
  const SCARD_IO_REQUEST *sendPci = NULL;
  SCARD_IO_REQUEST *recvPci = NULL;
  BYTE *sendBuffer;
  BYTE *recvBuffer;
  DWORD sendLen, recvLen;
  zval *argb = NULL;
  LONG rc;
  PARSE_ARGS(0, 3);

  /* Retrieve parameters */
  hCard = hLastCard;
  argb  = ARG(0);
  if (argc >= 2)
  {
    convert_to_long(ARG(0));
    hCard         = ARG(0)->value.lval;
    argb          = ARG(1);
  }

  /* Are we in T=0 or T=1 ? */
  rc = SCardStatus(hCard, NULL, NULL, &dwState, &dwProtocol, NULL, NULL);
  if (rc != SCARD_S_SUCCESS)
  {
    lLastError = rc;
    RETURN_FALSE;
  }
        
  if (!(dwState & SCARD_POWERED))
    RETURN_FALSE;

  switch (dwProtocol)
  {
    case SCARD_PROTOCOL_RAW : sendPci = SCARD_PCI_RAW; break;
    case SCARD_PROTOCOL_T0  : sendPci = SCARD_PCI_T0;  break;
    case SCARD_PROTOCOL_T1  : sendPci = SCARD_PCI_T1;  break;
  }

  /* Get buffer to send */
  convert_to_string(argb);
  sendBuffer = e_hex_to_bytes(argb->value.str.val, &sendLen);

  /* Guess the size of the buffer to recv */
  recvLen    = 2+256;
  recvBuffer = emalloc(recvLen);

  /* Perform the exchange */
  recvPci = emalloc(1024);
  recvPci->dwProtocol  = dwProtocol;
  recvPci->cbPciLength = 1024;

  rc = SCardTransmit(hCard, sendPci, sendBuffer, sendLen, recvPci, recvBuffer, &recvLen);
  if (rc != SCARD_S_SUCCESS)
  {
    efree(recvPci);
    efree(recvBuffer);
    efree(sendBuffer);
    lLastError = rc;
    RETURN_FALSE;
  }
  efree(recvPci);

  /* Return the response */
  RETVAL_STRING(e_bytes_to_hex(recvBuffer, recvLen), TRUE);

  /* Free local data */
  efree(recvBuffer);
  efree(sendBuffer);
}
/* }}} */

/* {{{ proto long scardgetlasterror()
   Retrieve value of last error */
PHP_FUNCTION(scardgetlasterror)
{
  RETVAL_LONG(lLastError);
  lLastError = SCARD_S_SUCCESS;
}
/* }}} */
