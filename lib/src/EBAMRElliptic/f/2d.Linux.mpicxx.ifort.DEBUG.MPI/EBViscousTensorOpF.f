      subroutine CELLGRADEBVTOP(
     & grad
     & ,igradlo0,igradlo1
     & ,igradhi0,igradhi1
     & ,vel
     & ,ivello0,ivello1
     & ,ivelhi0,ivelhi1
     & ,dx
     & ,iloboxlo0,iloboxlo1
     & ,iloboxhi0,iloboxhi1
     & ,ihiboxlo0,ihiboxlo1
     & ,ihiboxhi0,ihiboxhi1
     & ,icenterboxlo0,icenterboxlo1
     & ,icenterboxhi0,icenterboxhi1
     & ,haslo
     & ,hashi
     & ,divdir
     & )
      implicit none
      integer CHF_ID(0:5,0:5)
      data CHF_ID/ 1,0,0,0,0,0 ,0,1,0,0,0,0 ,0,0,1,0,0,0 ,0,0,0,1,0,0 ,0
     &,0,0,0,1,0 ,0,0,0,0,0,1 /
      integer igradlo0,igradlo1
      integer igradhi0,igradhi1
      REAL*8 grad(
     & igradlo0:igradhi0,
     & igradlo1:igradhi1)
      integer ivello0,ivello1
      integer ivelhi0,ivelhi1
      REAL*8 vel(
     & ivello0:ivelhi0,
     & ivello1:ivelhi1)
      REAL*8 dx
      integer iloboxlo0,iloboxlo1
      integer iloboxhi0,iloboxhi1
      integer ihiboxlo0,ihiboxlo1
      integer ihiboxhi0,ihiboxhi1
      integer icenterboxlo0,icenterboxlo1
      integer icenterboxhi0,icenterboxhi1
      integer haslo
      integer hashi
      integer divdir
      integer ii,i,jj,j
      ii = chf_id(divdir, 0)
      jj = chf_id(divdir, 1)
      do j = icenterboxlo1,icenterboxhi1
      do i = icenterboxlo0,icenterboxhi0
      grad(i,j) =
     $ ( vel(i+ii,j+jj)
     $ - vel(i-ii,j-jj) )/((2.0d0)*dx)
      enddo
      enddo
      if(haslo.eq.1) then
      do j = iloboxlo1,iloboxhi1
      do i = iloboxlo0,iloboxhi0
         grad(i,j) =
     $ ( vel(i+ii,j+jj)
     $ - vel(i ,j ) )/(dx)
      enddo
      enddo
      endif
      if(hashi.eq.1) then
      do j = ihiboxlo1,ihiboxhi1
      do i = ihiboxlo0,ihiboxhi0
         grad(i,j) =
     $ ( vel(i ,j )
     $ - vel(i-ii,j-jj) )/(dx)
      enddo
      enddo
      endif
      return
      end
      subroutine INCRAPPLYEBVTOP(
     & lhs
     & ,ilhslo0,ilhslo1
     & ,ilhshi0,ilhshi1
     & ,interiorflux
     & ,iinteriorfluxlo0,iinteriorfluxlo1
     & ,iinteriorfluxhi0,iinteriorfluxhi1
     & ,domainfluxlo
     & ,idomainfluxlolo0,idomainfluxlolo1
     & ,idomainfluxlohi0,idomainfluxlohi1
     & ,domainfluxhi
     & ,idomainfluxhilo0,idomainfluxhilo1
     & ,idomainfluxhihi0,idomainfluxhihi1
     & ,beta
     & ,dx
     & ,iloboxlo0,iloboxlo1
     & ,iloboxhi0,iloboxhi1
     & ,ihiboxlo0,ihiboxlo1
     & ,ihiboxhi0,ihiboxhi1
     & ,icenterboxlo0,icenterboxlo1
     & ,icenterboxhi0,icenterboxhi1
     & ,haslo
     & ,hashi
     & ,facedir
     & )
      implicit none
      integer CHF_ID(0:5,0:5)
      data CHF_ID/ 1,0,0,0,0,0 ,0,1,0,0,0,0 ,0,0,1,0,0,0 ,0,0,0,1,0,0 ,0
     &,0,0,0,1,0 ,0,0,0,0,0,1 /
      integer ilhslo0,ilhslo1
      integer ilhshi0,ilhshi1
      REAL*8 lhs(
     & ilhslo0:ilhshi0,
     & ilhslo1:ilhshi1)
      integer iinteriorfluxlo0,iinteriorfluxlo1
      integer iinteriorfluxhi0,iinteriorfluxhi1
      REAL*8 interiorflux(
     & iinteriorfluxlo0:iinteriorfluxhi0,
     & iinteriorfluxlo1:iinteriorfluxhi1)
      integer idomainfluxlolo0,idomainfluxlolo1
      integer idomainfluxlohi0,idomainfluxlohi1
      REAL*8 domainfluxlo(
     & idomainfluxlolo0:idomainfluxlohi0,
     & idomainfluxlolo1:idomainfluxlohi1)
      integer idomainfluxhilo0,idomainfluxhilo1
      integer idomainfluxhihi0,idomainfluxhihi1
      REAL*8 domainfluxhi(
     & idomainfluxhilo0:idomainfluxhihi0,
     & idomainfluxhilo1:idomainfluxhihi1)
      REAL*8 beta
      REAL*8 dx
      integer iloboxlo0,iloboxlo1
      integer iloboxhi0,iloboxhi1
      integer ihiboxlo0,ihiboxlo1
      integer ihiboxhi0,ihiboxhi1
      integer icenterboxlo0,icenterboxlo1
      integer icenterboxhi0,icenterboxhi1
      integer haslo
      integer hashi
      integer facedir
      integer ii,i,jj,j
      ii = chf_id(facedir, 0)
      jj = chf_id(facedir, 1)
      do j = icenterboxlo1,icenterboxhi1
      do i = icenterboxlo0,icenterboxhi0
      lhs(i,j) = lhs(i,j)
     $ +beta*
     $ (interiorflux(i+ii,j+jj)
     $ -interiorflux(i ,j ))/dx
      enddo
      enddo
      if(haslo .eq. 1) then
      do j = iloboxlo1,iloboxhi1
      do i = iloboxlo0,iloboxhi0
         lhs(i,j) = lhs(i,j)
     $ + beta*
     $ (interiorflux(i+ii,j+jj)
     $ -domainfluxlo(i ,j ))/dx
      enddo
      enddo
      endif
      if(hashi .eq. 1) then
      do j = ihiboxlo1,ihiboxhi1
      do i = ihiboxlo0,ihiboxhi0
         lhs(i,j) = lhs(i,j)
     $ + beta*
     $ (domainfluxhi(i+ii,j+jj)
     $ -interiorflux(i ,j ))/dx
      enddo
      enddo
      endif
      return
      end
      subroutine NORMALGRADVISCDIRCH(
     & gradvelface
     & ,igradvelfacelo0,igradvelfacelo1
     & ,igradvelfacehi0,igradvelfacehi1
     & ,velcomp
     & ,ivelcomplo0,ivelcomplo1
     & ,ivelcomphi0,ivelcomphi1
     & ,velvalu
     & ,ivelvalulo0,ivelvalulo1
     & ,ivelvaluhi0,ivelvaluhi1
     & ,ifaceboxlo0,ifaceboxlo1
     & ,ifaceboxhi0,ifaceboxhi1
     & ,dx
     & ,iside
     & ,divdir
     & )
      implicit none
      integer CHF_ID(0:5,0:5)
      data CHF_ID/ 1,0,0,0,0,0 ,0,1,0,0,0,0 ,0,0,1,0,0,0 ,0,0,0,1,0,0 ,0
     &,0,0,0,1,0 ,0,0,0,0,0,1 /
      integer igradvelfacelo0,igradvelfacelo1
      integer igradvelfacehi0,igradvelfacehi1
      REAL*8 gradvelface(
     & igradvelfacelo0:igradvelfacehi0,
     & igradvelfacelo1:igradvelfacehi1)
      integer ivelcomplo0,ivelcomplo1
      integer ivelcomphi0,ivelcomphi1
      REAL*8 velcomp(
     & ivelcomplo0:ivelcomphi0,
     & ivelcomplo1:ivelcomphi1)
      integer ivelvalulo0,ivelvalulo1
      integer ivelvaluhi0,ivelvaluhi1
      REAL*8 velvalu(
     & ivelvalulo0:ivelvaluhi0,
     & ivelvalulo1:ivelvaluhi1)
      integer ifaceboxlo0,ifaceboxlo1
      integer ifaceboxhi0,ifaceboxhi1
      REAL*8 dx
      integer iside
      integer divdir
      integer i,id,j,jd
      REAL*8 val0, val1, val2, denom
      id = chf_id(divdir, 0)
      jd = chf_id(divdir, 1)
      if(iside.eq.-1) then
      do j = ifaceboxlo1,ifaceboxhi1
      do i = ifaceboxlo0,ifaceboxhi0
         val0 = velvalu(i ,j )
         val1 = velcomp(i ,j )
         val2 = velcomp(i+id,j+jd)
         denom = (0.500d0)*dx
         gradvelface(i,j) = (val1-val0)/denom
      enddo
      enddo
      else
      do j = ifaceboxlo1,ifaceboxhi1
      do i = ifaceboxlo0,ifaceboxhi0
         val0 = velvalu(i ,j )
         val1 = velcomp(i- id,j- jd)
         val2 = velcomp(i-2*id,j-2*jd)
         denom = -(0.500d0)*dx
         gradvelface(i,j) = (val1-val0)/denom
      enddo
      enddo
      endif
      return
      end
      subroutine SLIPWALLGRAD(
     & gradvelface
     & ,igradvelfacelo0,igradvelfacelo1
     & ,igradvelfacehi0,igradvelfacehi1
     & ,velcomp
     & ,ivelcomplo0,ivelcomplo1
     & ,ivelcomphi0,ivelcomphi1
     & ,ifaceboxlo0,ifaceboxlo1
     & ,ifaceboxhi0,ifaceboxhi1
     & ,dx
     & ,veldir
     & ,divdir
     & ,iside
     & ,iloboxlo0,iloboxlo1
     & ,iloboxhi0,iloboxhi1
     & ,ihiboxlo0,ihiboxlo1
     & ,ihiboxhi0,ihiboxhi1
     & ,icenterboxlo0,icenterboxlo1
     & ,icenterboxhi0,icenterboxhi1
     & ,haslo
     & ,hashi
     & ,facedir
     & )
      implicit none
      integer CHF_ID(0:5,0:5)
      data CHF_ID/ 1,0,0,0,0,0 ,0,1,0,0,0,0 ,0,0,1,0,0,0 ,0,0,0,1,0,0 ,0
     &,0,0,0,1,0 ,0,0,0,0,0,1 /
      integer igradvelfacelo0,igradvelfacelo1
      integer igradvelfacehi0,igradvelfacehi1
      REAL*8 gradvelface(
     & igradvelfacelo0:igradvelfacehi0,
     & igradvelfacelo1:igradvelfacehi1)
      integer ivelcomplo0,ivelcomplo1
      integer ivelcomphi0,ivelcomphi1
      REAL*8 velcomp(
     & ivelcomplo0:ivelcomphi0,
     & ivelcomplo1:ivelcomphi1)
      integer ifaceboxlo0,ifaceboxlo1
      integer ifaceboxhi0,ifaceboxhi1
      REAL*8 dx
      integer veldir
      integer divdir
      integer iside
      integer iloboxlo0,iloboxlo1
      integer iloboxhi0,iloboxhi1
      integer ihiboxlo0,ihiboxlo1
      integer ihiboxhi0,ihiboxhi1
      integer icenterboxlo0,icenterboxlo1
      integer icenterboxhi0,icenterboxhi1
      integer haslo
      integer hashi
      integer facedir
      integer i,id,iv,j,jd,jv
      REAL*8 val1, val2
      id = chf_id(facedir, 0)
      jd = chf_id(facedir, 1)
      iv = chf_id(divdir, 0)
      jv = chf_id(divdir, 1)
      if(facedir.eq.veldir) then
         if(iside.eq.-1) then
      do j = ifaceboxlo1,ifaceboxhi1
      do i = ifaceboxlo0,ifaceboxhi0
            val1 = velcomp(i ,j )
            gradvelface(i,j) = (2.0d0)*val1/dx
      enddo
      enddo
         else
      do j = ifaceboxlo1,ifaceboxhi1
      do i = ifaceboxlo0,ifaceboxhi0
            val1 = velcomp(i- id,j- jd)
            gradvelface(i,j) = -(2.0d0)*val1/dx
      enddo
      enddo
         endif
      else
         if(iside.eq.-1) then
      do j = icenterboxlo1,icenterboxhi1
      do i = icenterboxlo0,icenterboxhi0
            val1 = velcomp(i+iv,j+jv)
            val2 = velcomp(i-iv,j-jv)
            gradvelface(i,j) = (val1-val2)/((2.0d0)*dx)
      enddo
      enddo
            if(haslo.eq.1) then
      do j = iloboxlo1,iloboxhi1
      do i = iloboxlo0,iloboxhi0
               val1 = velcomp(i+iv,j+jv)
               val2 = velcomp(i ,j )
               gradvelface(i,j) = (val1-val2)/(dx)
      enddo
      enddo
            endif
            if(hashi.eq.1) then
      do j = ihiboxlo1,ihiboxhi1
      do i = ihiboxlo0,ihiboxhi0
               val1 = velcomp(i ,j )
               val2 = velcomp(i-iv,j-jv)
               gradvelface(i,j) = (val1-val2)/(dx)
      enddo
      enddo
            endif
         else
      do j = icenterboxlo1,icenterboxhi1
      do i = icenterboxlo0,icenterboxhi0
            val1 = velcomp(i-id+iv,j-jd+jv)
            val2 = velcomp(i-id-iv,j-jd-jv)
            gradvelface(i,j) = (val1-val2)/((2.0d0)*dx)
      enddo
      enddo
         if(haslo.eq.1) then
      do j = iloboxlo1,iloboxhi1
      do i = iloboxlo0,iloboxhi0
            val1 = velcomp(i-id+iv,j-jd+jv)
            val2 = velcomp(i-id ,j-jd )
            gradvelface(i,j) = (val1-val2)/(dx)
      enddo
      enddo
         endif
         if(hashi.eq.1) then
      do j = ihiboxlo1,ihiboxhi1
      do i = ihiboxlo0,ihiboxhi0
            val1 = velcomp(i-id ,j-jd )
            val2 = velcomp(i-id-iv,j-jd-jv)
            gradvelface(i,j) = (val1-val2)/(dx)
      enddo
      enddo
         endif
         endif
      endif
      return
      end
      subroutine VELDOTSIGMA(
     & veldotsig
     & ,iveldotsiglo0,iveldotsiglo1
     & ,iveldotsighi0,iveldotsighi1
     & ,nveldotsigcomp
     & ,vel
     & ,ivello0,ivello1
     & ,ivelhi0,ivelhi1
     & ,nvelcomp
     & ,sig
     & ,isiglo0,isiglo1
     & ,isighi0,isighi1
     & ,nsigcomp
     & ,ifaceboxlo0,ifaceboxlo1
     & ,ifaceboxhi0,ifaceboxhi1
     & )
      implicit none
      integer nveldotsigcomp
      integer iveldotsiglo0,iveldotsiglo1
      integer iveldotsighi0,iveldotsighi1
      REAL*8 veldotsig(
     & iveldotsiglo0:iveldotsighi0,
     & iveldotsiglo1:iveldotsighi1,
     & 0:nveldotsigcomp-1)
      integer nvelcomp
      integer ivello0,ivello1
      integer ivelhi0,ivelhi1
      REAL*8 vel(
     & ivello0:ivelhi0,
     & ivello1:ivelhi1,
     & 0:nvelcomp-1)
      integer nsigcomp
      integer isiglo0,isiglo1
      integer isighi0,isighi1
      REAL*8 sig(
     & isiglo0:isighi0,
     & isiglo1:isighi1,
     & 0:nsigcomp-1)
      integer ifaceboxlo0,ifaceboxlo1
      integer ifaceboxhi0,ifaceboxhi1
      integer i,j
      integer icomp
      REAL*8 sum
      do j = ifaceboxlo1,ifaceboxhi1
      do i = ifaceboxlo0,ifaceboxhi0
      sum = (0.0d0)
      do icomp = 0, 2 -1
         sum = sum + vel(i,j, icomp)*sig(i,j, icomp)
      enddo
      veldotsig(i,j, 0) = sum
      enddo
      enddo
      return
      end
      subroutine INCRPOINTDOTPROD(
     & sigmadotgradu
     & ,isigmadotgradulo0,isigmadotgradulo1
     & ,isigmadotgraduhi0,isigmadotgraduhi1
     & ,gradu
     & ,igradulo0,igradulo1
     & ,igraduhi0,igraduhi1
     & ,sigma
     & ,isigmalo0,isigmalo1
     & ,isigmahi0,isigmahi1
     & ,iboxlo0,iboxlo1
     & ,iboxhi0,iboxhi1
     & )
      implicit none
      integer isigmadotgradulo0,isigmadotgradulo1
      integer isigmadotgraduhi0,isigmadotgraduhi1
      REAL*8 sigmadotgradu(
     & isigmadotgradulo0:isigmadotgraduhi0,
     & isigmadotgradulo1:isigmadotgraduhi1)
      integer igradulo0,igradulo1
      integer igraduhi0,igraduhi1
      REAL*8 gradu(
     & igradulo0:igraduhi0,
     & igradulo1:igraduhi1)
      integer isigmalo0,isigmalo1
      integer isigmahi0,isigmahi1
      REAL*8 sigma(
     & isigmalo0:isigmahi0,
     & isigmalo1:isigmahi1)
      integer iboxlo0,iboxlo1
      integer iboxhi0,iboxhi1
      integer i,j
      REAL*8 incr
      do j = iboxlo1,iboxhi1
      do i = iboxlo0,iboxhi0
      incr = gradu(i,j)*sigma(i,j)
      sigmadotgradu(i,j) = sigmadotgradu(i,j) + incr
      enddo
      enddo
      return
      end
      subroutine INCRCCSIGMALAMBDA(
     & sigma
     & ,isigmalo0,isigmalo1
     & ,isigmahi0,isigmahi1
     & ,gradu
     & ,igradulo0,igradulo1
     & ,igraduhi0,igraduhi1
     & ,ngraducomp
     & ,lambda
     & ,ilambdalo0,ilambdalo1
     & ,ilambdahi0,ilambdahi1
     & ,igridlo0,igridlo1
     & ,igridhi0,igridhi1
     & ,diagcomp
     & )
      implicit none
      integer isigmalo0,isigmalo1
      integer isigmahi0,isigmahi1
      REAL*8 sigma(
     & isigmalo0:isigmahi0,
     & isigmalo1:isigmahi1)
      integer ngraducomp
      integer igradulo0,igradulo1
      integer igraduhi0,igraduhi1
      REAL*8 gradu(
     & igradulo0:igraduhi0,
     & igradulo1:igraduhi1,
     & 0:ngraducomp-1)
      integer ilambdalo0,ilambdalo1
      integer ilambdahi0,ilambdahi1
      REAL*8 lambda(
     & ilambdalo0:ilambdahi0,
     & ilambdalo1:ilambdahi1)
      integer igridlo0,igridlo1
      integer igridhi0,igridhi1
      integer diagcomp
      integer i,j
      do j = igridlo1,igridhi1
      do i = igridlo0,igridhi0
        sigma(i,j) = sigma(i,j)
     $ + lambda(i,j)*gradu(i,j, diagcomp)
      enddo
      enddo
      return
      end
      subroutine INCRCCSIGMAETA(
     & sigma
     & ,isigmalo0,isigmalo1
     & ,isigmahi0,isigmahi1
     & ,gradu
     & ,igradulo0,igradulo1
     & ,igraduhi0,igraduhi1
     & ,ngraducomp
     & ,eta
     & ,ietalo0,ietalo1
     & ,ietahi0,ietahi1
     & ,igridlo0,igridlo1
     & ,igridhi0,igridhi1
     & ,gradcomp
     & ,trancomp
     & )
      implicit none
      integer isigmalo0,isigmalo1
      integer isigmahi0,isigmahi1
      REAL*8 sigma(
     & isigmalo0:isigmahi0,
     & isigmalo1:isigmahi1)
      integer ngraducomp
      integer igradulo0,igradulo1
      integer igraduhi0,igraduhi1
      REAL*8 gradu(
     & igradulo0:igraduhi0,
     & igradulo1:igraduhi1,
     & 0:ngraducomp-1)
      integer ietalo0,ietalo1
      integer ietahi0,ietahi1
      REAL*8 eta(
     & ietalo0:ietahi0,
     & ietalo1:ietahi1)
      integer igridlo0,igridlo1
      integer igridhi0,igridhi1
      integer gradcomp
      integer trancomp
      integer i,j
      do j = igridlo1,igridhi1
      do i = igridlo0,igridhi0
      sigma(i,j) = sigma(i,j)
     $ + eta(i,j)*
     $ (gradu(i,j, gradcomp)
     $ +gradu(i,j, trancomp))
      enddo
      enddo
      return
      end
      subroutine INCRFACETOCELLAVERAGE(
     & cellcoef
     & ,icellcoeflo0,icellcoeflo1
     & ,icellcoefhi0,icellcoefhi1
     & ,facecoef
     & ,ifacecoeflo0,ifacecoeflo1
     & ,ifacecoefhi0,ifacecoefhi1
     & ,facedir
     & ,igridlo0,igridlo1
     & ,igridhi0,igridhi1
     & ,nfacesper
     & )
      implicit none
      integer CHF_ID(0:5,0:5)
      data CHF_ID/ 1,0,0,0,0,0 ,0,1,0,0,0,0 ,0,0,1,0,0,0 ,0,0,0,1,0,0 ,0
     &,0,0,0,1,0 ,0,0,0,0,0,1 /
      integer icellcoeflo0,icellcoeflo1
      integer icellcoefhi0,icellcoefhi1
      REAL*8 cellcoef(
     & icellcoeflo0:icellcoefhi0,
     & icellcoeflo1:icellcoefhi1)
      integer ifacecoeflo0,ifacecoeflo1
      integer ifacecoefhi0,ifacecoefhi1
      REAL*8 facecoef(
     & ifacecoeflo0:ifacecoefhi0,
     & ifacecoeflo1:ifacecoefhi1)
      integer facedir
      integer igridlo0,igridlo1
      integer igridhi0,igridhi1
      REAL*8 nfacesper
      integer ii,i,jj,j
      ii = chf_id(facedir, 0)
      jj = chf_id(facedir, 1)
      do j = igridlo1,igridhi1
      do i = igridlo0,igridhi0
        cellcoef(i,j) = cellcoef(i,j) +
     $ (facecoef(i+ii,j+jj)
     $ +facecoef(i ,j ))/nfacesper
      enddo
      enddo
      return
      end
