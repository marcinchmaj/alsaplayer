## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
##
## If you would like to negotiate alternate licensing terms, you may do
## so by contacting the author: Andy Lo A Foe <andy@alsaplayer.org>
##

if ARCH_ULTRA

SUN_LIBS = -lresolv

endif

LIBS = -lpthread -ldl $(SUN_LIBS)

COMMON_FLAGS = @DFLAGS@ -D_REENTRANT -DADDON_DIR=\"$(ADDON_DIR)\"

INCLUDES = -I$(top_srcdir)/alsaplayer -I$(top_srcdir)/libalsaplayer

AM_CPPFLAGS = -I../intl -I$(top_srcdir)/intl

AM_CXXFLAGS = $(COMMON_FLAGS)

bin_PROGRAMS = alsaplayer

localedir = $(datadir)/locale
alsaplayer_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\"

alsaplayer_LDFLAGS = -export-dynamic

alsaplayer_SOURCES = AlsaSubscriber.cpp \
		AlsaNode.cpp Effects.cpp \
		Main.cpp CorePlayer.cpp Playlist.cpp  \
		SampleBuffer.cpp \
		reverbst.cpp \
		fft.c convolve.c utilities.c \
		ControlSocket.cpp \
		prefs.c reader.cpp

alsaplayer_LDADD = $(top_builddir)/libalsaplayer/libalsaplayer.la @LIBINTL@

jackplayer:
		ln -s alsaplayer jackplayer
