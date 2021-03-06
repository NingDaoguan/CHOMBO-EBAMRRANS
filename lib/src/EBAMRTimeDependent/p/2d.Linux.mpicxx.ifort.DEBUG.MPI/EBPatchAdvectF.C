#include "REAL.H"
#include "SPACE.H"
#include "CONSTANTS.H"

      subroutine PREDADVECT(
     &           idcalclo0,idcalclo1
     &           ,idcalchi0,idcalchi1
     &           ,rho
     &           ,irholo0,irholo1
     &           ,irhohi0,irhohi1
     &           ,drho
     &           ,idrholo0,idrholo1
     &           ,idrhohi0,idrhohi1
     &           ,velcc
     &           ,ivelcclo0,ivelcclo1
     &           ,ivelcchi0,ivelcchi1
     &           ,nvelcccomp
     &           ,rholo
     &           ,irhololo0,irhololo1
     &           ,irholohi0,irholohi1
     &           ,rhohi
     &           ,irhohilo0,irhohilo1
     &           ,irhohihi0,irhohihi1
     &           ,normdir
     &           ,dtbydx
     &           )

      implicit none
      integer idcalclo0,idcalclo1
      integer idcalchi0,idcalchi1
      integer irholo0,irholo1
      integer irhohi0,irhohi1
      REAL_T rho(
     &           irholo0:irhohi0,
     &           irholo1:irhohi1)
      integer idrholo0,idrholo1
      integer idrhohi0,idrhohi1
      REAL_T drho(
     &           idrholo0:idrhohi0,
     &           idrholo1:idrhohi1)
      integer nvelcccomp
      integer ivelcclo0,ivelcclo1
      integer ivelcchi0,ivelcchi1
      REAL_T velcc(
     &           ivelcclo0:ivelcchi0,
     &           ivelcclo1:ivelcchi1,
     &           0:nvelcccomp-1)
      integer irhololo0,irhololo1
      integer irholohi0,irholohi1
      REAL_T rholo(
     &           irhololo0:irholohi0,
     &           irhololo1:irholohi1)
      integer irhohilo0,irhohilo1
      integer irhohihi0,irhohihi1
      REAL_T rhohi(
     &           irhohilo0:irhohihi0,
     &           irhohilo1:irhohihi1)
      integer normdir
      REAL_T dtbydx
      real_t    veloc(0:CH_SPACEDIM-1)
      integer i,j, idir
      real_t dense, denlo, denhi, denslope
      
      do j = idcalclo1,idcalchi1
      do i = idcalclo0,idcalchi0

      dense    =  rho(i,j)
      denslope = drho(i,j)
      do idir = 0, CH_SPACEDIM-1
         veloc(idir)    = velcc(i,j,idir)
      enddo
      call pointpredadvect(
     &     dense, denlo, denhi, denslope, veloc,
     &     normdir, dtbydx)
      rholo(i,j)  = denlo
      rhohi(i,j)  = denhi
      
      enddo
      enddo
      return
      end
      subroutine POINTPREDADVECT(
     &           dense
     &           ,denlo
     &           ,denhi
     &           ,denslope
     &           ,veloc
     &           ,normdir
     &           ,dtbydx
     &           )

      implicit none
      REAL_T dense
      REAL_T denlo
      REAL_T denhi
      REAL_T denslope
      REAL_T veloc(0:1)
      integer normdir
      REAL_T dtbydx
      real_t velpos, velneg
      real_t tol
      denhi = dense + half*min((one-veloc(normdir)*dtbydx),one)*denslope
      denlo = dense - half*min((one+veloc(normdir)*dtbydx),one)*denslope
      return
      end
      subroutine PREDADVECTTRANS(
     &           idcalclo0,idcalclo1
     &           ,idcalchi0,idcalchi1
     &           ,rho
     &           ,irholo0,irholo1
     &           ,irhohi0,irhohi1
     &           ,drho
     &           ,idrholo0,idrholo1
     &           ,idrhohi0,idrhohi1
     &           ,velcc
     &           ,ivelcclo0,ivelcclo1
     &           ,ivelcchi0,ivelcchi1
     &           ,nvelcccomp
     &           ,rholo
     &           ,irhololo0,irhololo1
     &           ,irholohi0,irholohi1
     &           ,rhohi
     &           ,irhohilo0,irhohilo1
     &           ,irhohihi0,irhohihi1
     &           ,tandir
     &           ,dtbydx
     &           )

      implicit none
      integer idcalclo0,idcalclo1
      integer idcalchi0,idcalchi1
      integer irholo0,irholo1
      integer irhohi0,irhohi1
      REAL_T rho(
     &           irholo0:irhohi0,
     &           irholo1:irhohi1)
      integer idrholo0,idrholo1
      integer idrhohi0,idrhohi1
      REAL_T drho(
     &           idrholo0:idrhohi0,
     &           idrholo1:idrhohi1)
      integer nvelcccomp
      integer ivelcclo0,ivelcclo1
      integer ivelcchi0,ivelcchi1
      REAL_T velcc(
     &           ivelcclo0:ivelcchi0,
     &           ivelcclo1:ivelcchi1,
     &           0:nvelcccomp-1)
      integer irhololo0,irhololo1
      integer irholohi0,irholohi1
      REAL_T rholo(
     &           irhololo0:irholohi0,
     &           irhololo1:irholohi1)
      integer irhohilo0,irhohilo1
      integer irhohihi0,irhohihi1
      REAL_T rhohi(
     &           irhohilo0:irhohihi0,
     &           irhohilo1:irhohihi1)
      integer tandir
      REAL_T dtbydx
      real_t    veloc(0:CH_SPACEDIM-1)
      integer i,j, idir
      real_t dense, denlo, denhi, denslope
      
      do j = idcalclo1,idcalchi1
      do i = idcalclo0,idcalchi0

      dense    =   rho(i,j)
      denslope =  drho(i,j)
      denlo    = rholo(i,j)
      denhi    = rhohi(i,j)
      do idir = 0, CH_SPACEDIM-1
         veloc(idir)    = velcc(i,j,idir)
      enddo
      call pointpredadvecttrans(
     &     dense, denlo, denhi, denslope, veloc,
     &     tandir, dtbydx)
      rholo(i,j)  = denlo
      rhohi(i,j)  = denhi
      
      enddo
      enddo
      return
      end
      subroutine POINTPREDADVECTTRANS(
     &           dense
     &           ,denlo
     &           ,denhi
     &           ,denslope
     &           ,veloc
     &           ,tandir
     &           ,dtbydx
     &           )

      implicit none
      REAL_T dense
      REAL_T denlo
      REAL_T denhi
      REAL_T denslope
      REAL_T veloc(0:1)
      integer tandir
      REAL_T dtbydx
      real_t velpos, velneg
      real_t tol
      denhi = denhi - half*dtbydx*veloc(tandir)*denslope
      denlo = denlo - half*dtbydx*veloc(tandir)*denslope
      return
      end
#include "CONSTANTS.H"
      subroutine GETDSDT(
     &           dsdtplus
     &           ,idsdtpluslo0,idsdtpluslo1
     &           ,idsdtplushi0,idsdtplushi1
     &           ,ndsdtpluscomp
     &           ,dsdtminu
     &           ,idsdtminulo0,idsdtminulo1
     &           ,idsdtminuhi0,idsdtminuhi1
     &           ,ndsdtminucomp
     &           ,slopeprim
     &           ,islopeprimlo0,islopeprimlo1
     &           ,islopeprimhi0,islopeprimhi1
     &           ,nslopeprimcomp
     &           ,slopeupwi
     &           ,islopeupwilo0,islopeupwilo1
     &           ,islopeupwihi0,islopeupwihi1
     &           ,nslopeupwicomp
     &           ,normalvel
     &           ,inormalvello0,inormalvello1
     &           ,inormalvelhi0,inormalvelhi1
     &           ,nnormalvelcomp
     &           ,dx
     &           ,dt
     &           ,facedir
     &           ,extrapdir
     &           ,numslopes
     &           ,ientireboxlo0,ientireboxlo1
     &           ,ientireboxhi0,ientireboxhi1
     &           )

      implicit none
      integer ndsdtpluscomp
      integer idsdtpluslo0,idsdtpluslo1
      integer idsdtplushi0,idsdtplushi1
      REAL_T dsdtplus(
     &           idsdtpluslo0:idsdtplushi0,
     &           idsdtpluslo1:idsdtplushi1,
     &           0:ndsdtpluscomp-1)
      integer ndsdtminucomp
      integer idsdtminulo0,idsdtminulo1
      integer idsdtminuhi0,idsdtminuhi1
      REAL_T dsdtminu(
     &           idsdtminulo0:idsdtminuhi0,
     &           idsdtminulo1:idsdtminuhi1,
     &           0:ndsdtminucomp-1)
      integer nslopeprimcomp
      integer islopeprimlo0,islopeprimlo1
      integer islopeprimhi0,islopeprimhi1
      REAL_T slopeprim(
     &           islopeprimlo0:islopeprimhi0,
     &           islopeprimlo1:islopeprimhi1,
     &           0:nslopeprimcomp-1)
      integer nslopeupwicomp
      integer islopeupwilo0,islopeupwilo1
      integer islopeupwihi0,islopeupwihi1
      REAL_T slopeupwi(
     &           islopeupwilo0:islopeupwihi0,
     &           islopeupwilo1:islopeupwihi1,
     &           0:nslopeupwicomp-1)
      integer nnormalvelcomp
      integer inormalvello0,inormalvello1
      integer inormalvelhi0,inormalvelhi1
      REAL_T normalvel(
     &           inormalvello0:inormalvelhi0,
     &           inormalvello1:inormalvelhi1,
     &           0:nnormalvelcomp-1)
      REAL_T dx
      REAL_T dt
      integer facedir
      integer extrapdir
      integer numslopes
      integer ientireboxlo0,ientireboxlo1
      integer ientireboxhi0,ientireboxhi1
      integer i   ,j   ,lvar
      real_t velpt, dw, velplus, velminu
      do lvar = 0, numslopes - 1
         
      do j = ientireboxlo1,ientireboxhi1
      do i = ientireboxlo0,ientireboxhi0

         velpt = normalvel(i,j,extrapdir)
         if(extrapdir .eq. facedir) then
            dw = slopeprim(i,j, lvar)
            velplus = max(velpt, zero)
            velminu = min(velpt, zero)
         else
            dw = slopeupwi(i,j, lvar)
            velplus = velpt
            velminu = velpt
         endif
         dsdtplus(i,j,lvar) =
     $        dsdtplus(i,j,lvar) - velplus*dw/dx
         dsdtminu(i,j,lvar) =
     $        dsdtminu(i,j,lvar) - velminu*dw/dx
         
      enddo
      enddo
      enddo
      return
      end
      subroutine UPWINDDIFFS(
     &           slopeupwi
     &           ,islopeupwilo0,islopeupwilo1
     &           ,islopeupwihi0,islopeupwihi1
     &           ,nslopeupwicomp
     &           ,primstate
     &           ,iprimstatelo0,iprimstatelo1
     &           ,iprimstatehi0,iprimstatehi1
     &           ,nprimstatecomp
     &           ,normalvel
     &           ,inormalvello0,inormalvello1
     &           ,inormalvelhi0,inormalvelhi1
     &           ,nnormalvelcomp
     &           ,numslopes
     &           ,idir
     &           ,iloboxlo0,iloboxlo1
     &           ,iloboxhi0,iloboxhi1
     &           ,haslo
     &           ,ihiboxlo0,ihiboxlo1
     &           ,ihiboxhi0,ihiboxhi1
     &           ,hashi
     &           ,icenterboxlo0,icenterboxlo1
     &           ,icenterboxhi0,icenterboxhi1
     &           )

      implicit none
      integer CHF_ID(0:5,0:5)
      data CHF_ID/ 1,0,0,0,0,0 ,0,1,0,0,0,0 ,0,0,1,0,0,0 ,0,0,0,1,0,0 ,0,0,0,0,1,0 ,0,0,0,0,0,1 /


      integer nslopeupwicomp
      integer islopeupwilo0,islopeupwilo1
      integer islopeupwihi0,islopeupwihi1
      REAL_T slopeupwi(
     &           islopeupwilo0:islopeupwihi0,
     &           islopeupwilo1:islopeupwihi1,
     &           0:nslopeupwicomp-1)
      integer nprimstatecomp
      integer iprimstatelo0,iprimstatelo1
      integer iprimstatehi0,iprimstatehi1
      REAL_T primstate(
     &           iprimstatelo0:iprimstatehi0,
     &           iprimstatelo1:iprimstatehi1,
     &           0:nprimstatecomp-1)
      integer nnormalvelcomp
      integer inormalvello0,inormalvello1
      integer inormalvelhi0,inormalvelhi1
      REAL_T normalvel(
     &           inormalvello0:inormalvelhi0,
     &           inormalvello1:inormalvelhi1,
     &           0:nnormalvelcomp-1)
      integer numslopes
      integer idir
      integer iloboxlo0,iloboxlo1
      integer iloboxhi0,iloboxhi1
      integer haslo
      integer ihiboxlo0,ihiboxlo1
      integer ihiboxhi0,ihiboxhi1
      integer hashi
      integer icenterboxlo0,icenterboxlo1
      integer icenterboxhi0,icenterboxhi1
      integer i   ,j   ,lvar
      integer ioff,joff
      real_t dwr,dwl,velpt, dw
      real_t tol
      tol = 1.e-12
      
      ioff = chf_id(0,idir)
      joff = chf_id(1,idir)
      do lvar = 0, numslopes - 1
         
      do j = icenterboxlo1,icenterboxhi1
      do i = icenterboxlo0,icenterboxhi0

         velpt = normalvel(i,j,idir)
         dwr =  primstate(i+ioff,j+joff,lvar)
     &        - primstate(i     ,j     ,lvar)
         dwl =  primstate(i     ,j     ,lvar)
     &        - primstate(i-ioff,j-joff,lvar)
         if(velpt .gt. tol) then
            dw = dwl
         else if(velpt .lt. -tol) then
            dw = dwr
         else
            dw = half*(dwl+dwr)
         endif
         slopeupwi(i,j,lvar) = dw
         
      enddo
      enddo
         if (haslo .ne. 0) then
            
      do j = iloboxlo1,iloboxhi1
      do i = iloboxlo0,iloboxhi0

            velpt = normalvel(i,j,idir)
            dwl = 0.d0
            dwr =  primstate(i+ioff,j+joff,lvar)
     &           - primstate(i     ,j     ,lvar)
            dw = dwr
            slopeupwi(i,j,lvar) = dw
            
      enddo
      enddo
         endif
         if (hashi .ne. 0) then
            
      do j = ihiboxlo1,ihiboxhi1
      do i = ihiboxlo0,ihiboxhi0

            velpt = normalvel(i,j,idir)
            dwl =  primstate(i     ,j     ,lvar)
     &           - primstate(i-ioff,j-joff,lvar)
            dwr = 0.d0
            dw = dwl
            slopeupwi(i,j,lvar) = dw
            
      enddo
      enddo
         endif
      enddo
      return
      end
      subroutine ADVECTIVEF(
     &           udelrho
     &           ,iudelrholo0,iudelrholo1
     &           ,iudelrhohi0,iudelrhohi1
     &           ,nudelrhocomp
     &           ,facerho
     &           ,ifacerholo0,ifacerholo1
     &           ,ifacerhohi0,ifacerhohi1
     &           ,nfacerhocomp
     &           ,facevel
     &           ,ifacevello0,ifacevello1
     &           ,ifacevelhi0,ifacevelhi1
     &           ,facedir
     &           ,nconserved
     &           ,dx
     &           ,idcalclo0,idcalclo1
     &           ,idcalchi0,idcalchi1
     &           ,doingvel
     &           )

      implicit none
      integer CHF_ID(0:5,0:5)
      data CHF_ID/ 1,0,0,0,0,0 ,0,1,0,0,0,0 ,0,0,1,0,0,0 ,0,0,0,1,0,0 ,0,0,0,0,1,0 ,0,0,0,0,0,1 /


      integer nudelrhocomp
      integer iudelrholo0,iudelrholo1
      integer iudelrhohi0,iudelrhohi1
      REAL_T udelrho(
     &           iudelrholo0:iudelrhohi0,
     &           iudelrholo1:iudelrhohi1,
     &           0:nudelrhocomp-1)
      integer nfacerhocomp
      integer ifacerholo0,ifacerholo1
      integer ifacerhohi0,ifacerhohi1
      REAL_T facerho(
     &           ifacerholo0:ifacerhohi0,
     &           ifacerholo1:ifacerhohi1,
     &           0:nfacerhocomp-1)
      integer ifacevello0,ifacevello1
      integer ifacevelhi0,ifacevelhi1
      REAL_T facevel(
     &           ifacevello0:ifacevelhi0,
     &           ifacevello1:ifacevelhi1)
      integer facedir
      integer nconserved
      REAL_T dx
      integer idcalclo0,idcalclo1
      integer idcalchi0,idcalchi1
      integer doingvel
      integer i, j
      integer ioff, joff
      integer spacedim,iv
      real_t  uave, rhodiff, hival, loval
      
      ioff = chf_id(0,facedir)
      joff = chf_id(1,facedir)
      spacedim = CH_SPACEDIM
      if(doingvel .eq. 1) then
         do iv = 0,nconserved - 1
            
      do j = idcalclo1,idcalchi1
      do i = idcalclo0,idcalchi0

            uave =
     &           (facevel(i+ioff,j+joff)
     &           +facevel(i     ,j     ))/two
            rhodiff =
     &           (facerho(i+ioff,j+joff,iv)
     &           -facerho(i     ,j     ,iv))/dx
            udelrho(i,j,iv) = udelrho(i,j,iv) +  uave*rhodiff
            
      enddo
      enddo
         enddo
      else
         do iv = 0,nconserved - 1
            
      do j = idcalclo1,idcalchi1
      do i = idcalclo0,idcalchi0

            hival = facevel(i+ioff,j+joff)*facerho(i+ioff,j+joff,iv)
            loval = facevel(i     ,j     )*facerho(i     ,j     ,iv)
            udelrho(i,j,iv) = udelrho(i,j,iv) + (hival-loval)/dx
            
      enddo
      enddo
         enddo
      endif
      return
      end
      subroutine AVEFACETOCELL(
     &           cellvel
     &           ,icellvello0,icellvello1
     &           ,icellvelhi0,icellvelhi1
     &           ,ncellvelcomp
     &           ,facevel
     &           ,ifacevello0,ifacevello1
     &           ,ifacevelhi0,ifacevelhi1
     &           ,idir
     &           ,idcalclo0,idcalclo1
     &           ,idcalchi0,idcalchi1
     &           )

      implicit none
      integer CHF_ID(0:5,0:5)
      data CHF_ID/ 1,0,0,0,0,0 ,0,1,0,0,0,0 ,0,0,1,0,0,0 ,0,0,0,1,0,0 ,0,0,0,0,1,0 ,0,0,0,0,0,1 /


      integer ncellvelcomp
      integer icellvello0,icellvello1
      integer icellvelhi0,icellvelhi1
      REAL_T cellvel(
     &           icellvello0:icellvelhi0,
     &           icellvello1:icellvelhi1,
     &           0:ncellvelcomp-1)
      integer ifacevello0,ifacevello1
      integer ifacevelhi0,ifacevelhi1
      REAL_T facevel(
     &           ifacevello0:ifacevelhi0,
     &           ifacevello1:ifacevelhi1)
      integer idir
      integer idcalclo0,idcalclo1
      integer idcalchi0,idcalchi1
      integer i, j
      integer ii,jj,kk
      ii = chf_id(0,idir)
      jj = chf_id(1,idir)
      kk = chf_id(2,idir)
      
      do j = idcalclo1,idcalchi1
      do i = idcalclo0,idcalchi0

      cellvel(i,j,idir) =  half*(
     &     facevel(i   ,j   ) +
     &     facevel(i+ii,j+jj))
      
      enddo
      enddo
      return
      end
      subroutine ADVECTUPDATE(
     &           idcalclo0,idcalclo1
     &           ,idcalchi0,idcalchi1
     &           ,primminu
     &           ,iprimminulo0,iprimminulo1
     &           ,iprimminuhi0,iprimminuhi1
     &           ,nprimminucomp
     &           ,primplus
     &           ,iprimpluslo0,iprimpluslo1
     &           ,iprimplushi0,iprimplushi1
     &           ,nprimpluscomp
     &           ,primface
     &           ,iprimfacelo0,iprimfacelo1
     &           ,iprimfacehi0,iprimfacehi1
     &           ,nprimfacecomp
     &           ,normvel
     &           ,inormvello0,inormvello1
     &           ,inormvelhi0,inormvelhi1
     &           ,nnormvelcomp
     &           ,facedir
     &           ,nprim
     &           ,dtbydx
     &           ,icellboxlo0,icellboxlo1
     &           ,icellboxhi0,icellboxhi1
     &           )

      implicit none
      integer CHF_ID(0:5,0:5)
      data CHF_ID/ 1,0,0,0,0,0 ,0,1,0,0,0,0 ,0,0,1,0,0,0 ,0,0,0,1,0,0 ,0,0,0,0,1,0 ,0,0,0,0,0,1 /


      integer idcalclo0,idcalclo1
      integer idcalchi0,idcalchi1
      integer nprimminucomp
      integer iprimminulo0,iprimminulo1
      integer iprimminuhi0,iprimminuhi1
      REAL_T primminu(
     &           iprimminulo0:iprimminuhi0,
     &           iprimminulo1:iprimminuhi1,
     &           0:nprimminucomp-1)
      integer nprimpluscomp
      integer iprimpluslo0,iprimpluslo1
      integer iprimplushi0,iprimplushi1
      REAL_T primplus(
     &           iprimpluslo0:iprimplushi0,
     &           iprimpluslo1:iprimplushi1,
     &           0:nprimpluscomp-1)
      integer nprimfacecomp
      integer iprimfacelo0,iprimfacelo1
      integer iprimfacehi0,iprimfacehi1
      REAL_T primface(
     &           iprimfacelo0:iprimfacehi0,
     &           iprimfacelo1:iprimfacehi1,
     &           0:nprimfacecomp-1)
      integer nnormvelcomp
      integer inormvello0,inormvello1
      integer inormvelhi0,inormvelhi1
      REAL_T normvel(
     &           inormvello0:inormvelhi0,
     &           inormvello1:inormvelhi1,
     &           0:nnormvelcomp-1)
      integer facedir
      integer nprim
      REAL_T dtbydx
      integer icellboxlo0,icellboxlo1
      integer icellboxhi0,icellboxhi1
      real_t unorm
      real_t primdiff
      integer i, j
      integer ioff, joff
      integer spacedim,iv
      
      ioff = chf_id(0,facedir)
      joff = chf_id(1,facedir)
      spacedim = CH_SPACEDIM
      do iv = 0,nprim - 1
         
      do j = icellboxlo1,icellboxhi1
      do i = icellboxlo0,icellboxhi0

         unorm    = normvel(i,j, facedir)
         primdiff =
     $        ( primface(i+ioff,j+joff,iv)
     $        - primface(i     ,j     ,iv))
         primminu(i,j,iv) = primminu(i,j,iv) -
     &        dtbydx * unorm * primdiff
         primplus(i,j,iv) = primplus(i,j,iv) -
     &        dtbydx * unorm * primdiff
         
      enddo
      enddo
      enddo
      return
      end
      subroutine ADVECTRIEMANN(
     &           idcalclo0,idcalclo1
     &           ,idcalchi0,idcalchi1
     &           ,primgdnv
     &           ,iprimgdnvlo0,iprimgdnvlo1
     &           ,iprimgdnvhi0,iprimgdnvhi1
     &           ,nprimgdnvcomp
     &           ,primleft
     &           ,iprimleftlo0,iprimleftlo1
     &           ,iprimlefthi0,iprimlefthi1
     &           ,nprimleftcomp
     &           ,primrigh
     &           ,iprimrighlo0,iprimrighlo1
     &           ,iprimrighhi0,iprimrighhi1
     &           ,nprimrighcomp
     &           ,advectvel
     &           ,iadvectvello0,iadvectvello1
     &           ,iadvectvelhi0,iadvectvelhi1
     &           ,facedir
     &           ,nprim
     &           ,curcomp
     &           ,doingvel
     &           )

      implicit none
      integer CHF_ID(0:5,0:5)
      data CHF_ID/ 1,0,0,0,0,0 ,0,1,0,0,0,0 ,0,0,1,0,0,0 ,0,0,0,1,0,0 ,0,0,0,0,1,0 ,0,0,0,0,0,1 /


      integer idcalclo0,idcalclo1
      integer idcalchi0,idcalchi1
      integer nprimgdnvcomp
      integer iprimgdnvlo0,iprimgdnvlo1
      integer iprimgdnvhi0,iprimgdnvhi1
      REAL_T primgdnv(
     &           iprimgdnvlo0:iprimgdnvhi0,
     &           iprimgdnvlo1:iprimgdnvhi1,
     &           0:nprimgdnvcomp-1)
      integer nprimleftcomp
      integer iprimleftlo0,iprimleftlo1
      integer iprimlefthi0,iprimlefthi1
      REAL_T primleft(
     &           iprimleftlo0:iprimlefthi0,
     &           iprimleftlo1:iprimlefthi1,
     &           0:nprimleftcomp-1)
      integer nprimrighcomp
      integer iprimrighlo0,iprimrighlo1
      integer iprimrighhi0,iprimrighhi1
      REAL_T primrigh(
     &           iprimrighlo0:iprimrighhi0,
     &           iprimrighlo1:iprimrighhi1,
     &           0:nprimrighcomp-1)
      integer iadvectvello0,iadvectvello1
      integer iadvectvelhi0,iadvectvelhi1
      REAL_T advectvel(
     &           iadvectvello0:iadvectvelhi0,
     &           iadvectvello1:iadvectvelhi1)
      integer facedir
      integer nprim
      integer curcomp
      integer doingvel
      real_t  velhi, vello, velface
      real_t tol
      integer i, j
      integer ioff, joff
      integer spacedim,iv
      
      ioff = chf_id(0,facedir)
      joff = chf_id(1,facedir)
      spacedim = CH_SPACEDIM
      tol = 1.e-12
      do iv = 0,nprim - 1
         
      do j = idcalclo1,idcalchi1
      do i = idcalclo0,idcalchi0

         velface  = advectvel(i,j)
         if(velface.gt.tol) then
            primgdnv(i,j,iv) = primleft(i-ioff,j-joff,iv)
         else if(velface.lt.-tol) then
            primgdnv(i,j,iv) = primrigh(i,j,iv)
         else
            if( (doingvel .eq. 1) .and. (curcomp.eq.facedir)) then
               primgdnv(i,j,iv) = zero
            else
               primgdnv(i,j,iv) =
     $              half*(
     $              primrigh(i     ,j     ,iv) +
     $              primleft(i-ioff,j-joff,iv))
            endif
         endif
         
      enddo
      enddo
      enddo
      return
      end
