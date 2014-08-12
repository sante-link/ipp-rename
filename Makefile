PROG=	ipp-rename

CFLAGS+=	-I/usr/local/include
LDFLAGS+=	-L/usr/local/lib -lcups

NO_MAN=

.include <bsd.prog.mk>
