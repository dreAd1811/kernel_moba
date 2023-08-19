# SPDX-License-Identifier: GPL-2.0
#
# Makefile for asymmetric cryptographic keys
#

obj-$(CONFIG_ASYMMETRIC_KEY_TYPE) += asymmetric_keys.o

asymmetric_keys-y := \
	asymmetric_type.o \
	restrict.o \
	signature.o

obj-$(CONFIG_ASYMMETRIC_PUBLIC_KEY_SUBTYPE) += public_key.o

#
# X.509 Certificate handling
#
obj-$(CONFIG_X509_CERTIFICATE_PARSER) += x509_key_parser.o
x509_key_parser-y := \
<<<<<<< HEAD
	x509.asn1.o \
	x509_akid.asn1.o \
=======
	x509-asn1.o \
	x509_akid-asn1.o \
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	x509_cert_parser.o \
	x509_public_key.o

$(obj)/x509_cert_parser.o: \
<<<<<<< HEAD
	$(obj)/x509.asn1.h \
	$(obj)/x509_akid.asn1.h

$(obj)/x509.asn1.o: $(obj)/x509.asn1.c $(obj)/x509.asn1.h
$(obj)/x509_akid.asn1.o: $(obj)/x509_akid.asn1.c $(obj)/x509_akid.asn1.h
=======
	$(obj)/x509-asn1.h \
	$(obj)/x509_akid-asn1.h

$(obj)/x509-asn1.o: $(obj)/x509-asn1.c $(obj)/x509-asn1.h
$(obj)/x509_akid-asn1.o: $(obj)/x509_akid-asn1.c $(obj)/x509_akid-asn1.h

clean-files	+= x509-asn1.c x509-asn1.h
clean-files	+= x509_akid-asn1.c x509_akid-asn1.h
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#
# PKCS#7 message handling
#
obj-$(CONFIG_PKCS7_MESSAGE_PARSER) += pkcs7_message.o
pkcs7_message-y := \
<<<<<<< HEAD
	pkcs7.asn1.o \
=======
	pkcs7-asn1.o \
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	pkcs7_parser.o \
	pkcs7_trust.o \
	pkcs7_verify.o

<<<<<<< HEAD
$(obj)/pkcs7_parser.o: $(obj)/pkcs7.asn1.h
$(obj)/pkcs7.asn1.o: $(obj)/pkcs7.asn1.c $(obj)/pkcs7.asn1.h
=======
$(obj)/pkcs7_parser.o: $(obj)/pkcs7-asn1.h
$(obj)/pkcs7-asn1.o: $(obj)/pkcs7-asn1.c $(obj)/pkcs7-asn1.h

clean-files	+= pkcs7-asn1.c pkcs7-asn1.h
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#
# PKCS#7 parser testing key
#
obj-$(CONFIG_PKCS7_TEST_KEY) += pkcs7_test_key.o
pkcs7_test_key-y := \
	pkcs7_key_type.o

#
# Signed PE binary-wrapped key handling
#
obj-$(CONFIG_SIGNED_PE_FILE_VERIFICATION) += verify_signed_pefile.o

verify_signed_pefile-y := \
	verify_pefile.o \
	mscode_parser.o \
<<<<<<< HEAD
	mscode.asn1.o

$(obj)/mscode_parser.o: $(obj)/mscode.asn1.h $(obj)/mscode.asn1.h
$(obj)/mscode.asn1.o: $(obj)/mscode.asn1.c $(obj)/mscode.asn1.h
=======
	mscode-asn1.o

$(obj)/mscode_parser.o: $(obj)/mscode-asn1.h $(obj)/mscode-asn1.h
$(obj)/mscode-asn1.o: $(obj)/mscode-asn1.c $(obj)/mscode-asn1.h

clean-files	+= mscode-asn1.c mscode-asn1.h
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
