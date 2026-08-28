namespace th105 {
class CSelect {
public:
    CSelect();
    virtual ~CSelect();
private:
    unsigned char bytes_004[0x2ED4];
};
class CSelectSV : public CSelect { public: CSelectSV(); private: int tail_2ed8; };
class CSelectCL : public CSelect { public: CSelectCL(); private: int tail_2ed8; };
class CLoading {
public:
    CLoading();
    virtual ~CLoading();
private:
    unsigned char bytes_004[0xB8];
};
class CLoadingSV : public CLoading { public: CLoadingSV(); };
class CLoadingCL : public CLoading { public: CLoadingCL(); };
CSelectSV::CSelectSV() {}
CSelectCL::CSelectCL() {}
CLoadingSV::CLoadingSV() {}
CLoadingCL::CLoadingCL() {}
}
