#pragma once
#include"Common.h"
#include"Time.h"
class CLyrics
{
private:
	struct Lyric
	{
		Time time;
		wstring text;

		//����С�ں�����������ڶԸ�ʰ�ʱ���ǩ����
		bool operator<(const Lyric& lyric) const
		{
			return lyric.time > time;
		}

		//����һ��ƫ��������ʱ��
		Time GetTime(int offset) const
		{
			if (offset == 0)
				return time;
			else
				return time + offset;
		}
	};

	wstring m_file;		//����ļ����ļ���
	vector<Lyric> m_lyrics;		//����ÿһ���ʣ�����ʱ���ǩ���ı���
	vector<string> m_lyrics_str;	//����δ���ʱ���ǩ��ÿһ����
	CodeType m_code_type{ CodeType::ANSI };		//����ı��ı�������

	wstring m_id;		//����е�id��ǩ�������������еĸ���id�����Լ��ӵģ���׼��lrc�ļ�û�������ǩ��
	wstring m_ti;		//����е�ti��ǩ
	wstring m_ar;		//����е�ar��ǩ
	wstring m_al;		//����е�al��ǩ
	wstring m_by;		//����е�by��ǩ
	bool m_id_tag{ false };		//������Ƿ���id��ǩ
	bool m_ti_tag{ false };		//������Ƿ���ti��ǩ
	bool m_ar_tag{ false };		//������Ƿ���ar��ǩ
	bool m_al_tag{ false };		//������Ƿ���al��ǩ
	bool m_by_tag{ false };		//������Ƿ���by��ǩ

	int m_offset{};		//���ƫ����
	bool m_offset_tag{ false };		//����Ƿ����ƫ������ǩ
	int m_offset_tag_index{ -1 };			//ƫ������ǩ�ڵڼ��У���0��ʼ�ƣ�

	bool m_modified{ false };		//����Ƿ��Ѿ��޸�

	void DivideLyrics();		//������ļ���ֳ����ɾ��ʣ���������m_lyrics_str��
	void DisposeLyric();		//��ø���е�ʱ���ǩ�͸���ı��������ı���string����ת����wstring���ͣ�������m_lyrics��
	void JudgeCode();		//�жϸ�ʵı����ʽ

public:
	CLyrics(const wstring& file_name);
	CLyrics() {}
	bool IsEmpty() const;		//�ж��Ƿ��и��
	wstring GetLyric(Time time, int offset) const;		//����ʱ�䷵��һ���ʡ���2�����������0���򷵻ص�ǰʱ���Ӧ�ĸ�ʣ������-1�򷵻ص�ǰʱ���ǰһ���ʣ�1�򷵻غ�һ���ʣ��Դ����ơ�
	wstring GetLyric(int index) const;			//������������һ����
	int GetLyricProgress(Time time) const;		//����ʱ�䷵�ظ�ʱ������Ӧ�ĸ�ʵĽ��ȣ�0~1000��������ʹ����Կ���OK��ʽ��ʾ��
	int GetLyricIndex(Time time) const;			//����ʱ�䷵�ظ�ʱ���Ӧ�ĸ����ţ������жϸ���Ƿ��б仯��
	CodeType GetCodeType() const;		//��ø���ı��ı�������
	wstring GetPathName() const { return m_file; }		//��ȡ����ļ���·��+�ļ���
	wstring GetAllLyricText() const;		//�������и�ʣ�������ȫ������ı���������ʶ��ǩ��ʱ���ǩ��
	wstring GetLyricsString() const;		//�������и�ʵ��ַ������Ա������ʽ������ȫ����ǩ
	bool IsModified() const { return m_modified; }
	int GetLyricCount() const{ return m_lyrics.size(); }

	void SaveLyric();		//�����ʣ������ƫ�Ʊ�����offset��ǩ�У�
	void SaveLyric2();		//�����ʣ������ƫ�Ʊ��浽ÿ��ʱ���ǩ�У�

	void CombineSameTimeLyric();	//������������ͬʱ���ǩ�ĸ�ʣ������ı��ϲ�������һ��ʱ���ǩ�����ڴ������ص��Ĵ�����ĸ�ʣ���ʹ��ʱ����ȷ������Ѿ���ʱ���ǩ����
	void DeleteRedundantLyric();	//ɾ�������ʱ���ǩ����100���ӵĸ�ʣ�ʹ��ʱ����ȷ������Ѿ���ʱ���ǩ����

	void AdjustLyric(int offset);	//������ʵ�ƫ����

	wstring GetSongId() const { return m_id; }		//��ȡ�����ڸ���е����������ֵĸ���ID

	void ChineseTranslation(bool simplified);		//���ķ���ת��
};
