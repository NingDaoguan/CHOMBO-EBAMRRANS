        subroutine COPYCFFAB(
     & finelevel
     & ,ifinelevello0,ifinelevello1
     & ,ifinelevelhi0,ifinelevelhi1
     & ,coarlevel
     & ,icoarlevello0,icoarlevello1
     & ,icoarlevelhi0,icoarlevelhi1
     & ,icoarboxlo0,icoarboxlo1
     & ,icoarboxhi0,icoarboxhi1
     & ,irefboxlo0,irefboxlo1
     & ,irefboxhi0,irefboxhi1
     & ,reftocoar
     & )
      implicit none
      integer ifinelevello0,ifinelevello1
      integer ifinelevelhi0,ifinelevelhi1
      REAL*8 finelevel(
     & ifinelevello0:ifinelevelhi0,
     & ifinelevello1:ifinelevelhi1)
      integer icoarlevello0,icoarlevello1
      integer icoarlevelhi0,icoarlevelhi1
      REAL*8 coarlevel(
     & icoarlevello0:icoarlevelhi0,
     & icoarlevello1:icoarlevelhi1)
      integer icoarboxlo0,icoarboxlo1
      integer icoarboxhi0,icoarboxhi1
      integer irefboxlo0,irefboxlo1
      integer irefboxhi0,irefboxhi1
      integer reftocoar
        integer iic,jjc
        integer iie,jje
        integer iif,jjf
        REAL*8 coarval
      do jjc = icoarboxlo1,icoarboxhi1
      do iic = icoarboxlo0,icoarboxhi0
          coarval = coarlevel(iic,jjc)
      do jje = irefboxlo1,irefboxhi1
      do iie = irefboxlo0,irefboxhi0
            iif = reftocoar*iic + iie
            jjf = reftocoar*jjc + jje
            finelevel(iif,jjf) = coarval
      enddo
      enddo
      enddo
      enddo
        return
        end
