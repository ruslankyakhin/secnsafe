Name:           secnsafe 
Version:        1.0
Release:        1%{?dist}
Summary:        Host-based IDS
License:        GPL
URL:            http://adminofsystem.net
Source0:        %{name}-%{version}.tar.bz2
%description
		Host-based IDS
%prep
%setup -q -n %{name}

%install
rm -rf $RPM_BUILD_ROOT
/bin/mkdir -p %{buildroot}/etc/secnsafe
/bin/mkdir -p %{buildroot}/usr/bin
/bin/mkdir -p %{buildroot}/usr/share/man/man8
/usr/bin/install -g 0 -o 0 -m 0655 secnsafe %{buildroot}/usr/bin
/usr/bin/install -g 0 -o 0 -m 0644 secnsafe.conf %{buildroot}/etc/secnsafe
/usr/bin/install -g 0 -o 0 -m 0644 secnsafe.8 %{buildroot}/usr/share/man/man8
/usr/bin/gzip %{buildroot}/usr/share/man/man8/secnsafe.8
%files
/etc/secnsafe/secnsafe.conf
/usr/bin/secnsafe
/usr/share/man/man8/secnsafe.8.gz
%changelog
